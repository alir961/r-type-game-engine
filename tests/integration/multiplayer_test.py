#!/usr/bin/env python3
"""Headless multiplayer test for the R-Type server.

Starts the server, connects two clients speaking the game's UDP protocol and
checks that each player receives its own updates and sees the other player.
No SFML or display needed.

    python3 tests/integration/multiplayer_test.py build/out/server/r-type_server
"""

import random
import socket
import struct
import subprocess
import sys
import time

# Mirrors RType::MessageType (engine/include/engine/network/NetworkMessage.hpp)
CONNECT, CONNECT_CALLBACK, DISCONNECT, PLAYER_NAME = 2, 3, 4, 5
MOVE_DOWN, SHOOT, TICK = 9, 11, 14
# Message is { int type; char data[256]; } aligned to 128 bytes
MESSAGE_SIZE = 384
DATA_SIZE = 256


def pack(kind, text):
    return struct.pack(f"<i{DATA_SIZE}s", kind, text.encode()).ljust(MESSAGE_SIZE, b"\0")


def unpack(raw):
    kind = struct.unpack_from("<i", raw)[0]
    return kind, raw[4:4 + DATA_SIZE].split(b"\0", 1)[0].decode(errors="replace")


class Player:
    def __init__(self, port, name):
        self.name = name
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_RCVBUF, 4 << 20)
        self.sock.connect(("127.0.0.1", port))
        self.sock.setblocking(False)
        self.received = []
        self.id = None

    def send(self, kind, text):
        self.sock.send(pack(kind, text))

    def drain(self):
        while True:
            try:
                self.received.append(unpack(self.sock.recv(MESSAGE_SIZE)))
            except (BlockingIOError, ConnectionRefusedError):
                # ConnectionRefusedError: the server is gone, the checks report it
                return

    def join(self):
        self.send(CONNECT, "connect 1920.00 1080.00\n")
        deadline = time.time() + 2
        while self.id is None and time.time() < deadline:
            time.sleep(0.01)
            self.drain()
            for kind, text in self.received:
                if kind == CONNECT_CALLBACK:
                    self.id = int(text.split()[1])
        if self.id is None:
            raise AssertionError(f"{self.name}: no connect callback")
        self.send(PLAYER_NAME, f"player {self.id} {self.name}\n")

    def player_updates(self, player_id):
        """(x, y, health) for every 'player <id> ...' update received."""
        updates = []
        for kind, text in self.received:
            words = text.split()
            if kind == PLAYER_NAME and words[:2] == ["player", str(player_id)]:
                updates.append((float(words[7]), float(words[8]), int(words[5])))
        return updates

    def has_bullet_of(self, player_id):
        return any(text.split()[:2] == ["bulletPlayer", str(player_id)] for _, text in self.received)


def run_ticks(players, seconds, every_tick=None):
    end = time.time() + seconds
    while time.time() < end:
        for player in players:
            player.send(TICK, f"tick {player.id}\n")
            if every_tick:
                every_tick(player)
            player.drain()
        time.sleep(1 / 60)


def main():
    server_path = sys.argv[1] if len(sys.argv) > 1 else "build/out/server/r-type_server"
    port = random.randint(20000, 40000)
    server = subprocess.Popen([server_path, str(port)], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    failures = []

    def check(condition, label):
        print(("PASS " if condition else "FAIL ") + label)
        if not condition:
            failures.append(label)

    try:
        time.sleep(0.5)
        alice, bob = Player(port, "alice"), Player(port, "bob")
        alice.join()
        bob.join()
        check(alice.id != bob.id, f"players get distinct session ids ({alice.id}, {bob.id})")

        run_ticks([alice, bob], 0.5)
        check(server.poll() is None, "server keeps running with two players")
        alice_start = alice.player_updates(alice.id) or bob.player_updates(alice.id)
        check(bool(alice.player_updates(alice.id)), "alice receives her own player")
        check(bool(bob.player_updates(alice.id)), "bob sees alice")
        check(bool(alice.player_updates(bob.id)), "alice sees bob")

        moves = iter(range(5))  # a few steps only: players that touch each other both die

        def alice_moves_and_shoots(player):
            if player is alice:
                if next(moves, None) is not None:
                    player.send(MOVE_DOWN, f"move_down {alice.id}\n")
                player.send(SHOOT, f"bulletPlayer {alice.id}\n")

        run_ticks([alice, bob], 1.0, alice_moves_and_shoots)
        start_y = alice_start[0][1] if alice_start else float("inf")
        check(any(y > start_y for _, y, _ in alice.player_updates(alice.id)), "alice sees herself move")
        check(any(y > start_y for _, y, _ in bob.player_updates(alice.id)), "bob sees alice move")
        check(alice.has_bullet_of(alice.id), "alice sees her own bullets")
        check(bob.has_bullet_of(alice.id), "bob sees alice's bullets")

        # Garbage and stale sessions must not take the server down
        alice.send(TICK, "tick not-a-number\n")
        alice.send(TICK, "tick\n")
        alice.sock.send(struct.pack("<i", TICK) + b"tick")
        alice.sock.send(b"")
        alice.sock.send(b"\x01")
        bob.send(DISCONNECT, f"disconnect {bob.id}\n")
        bob.send(DISCONNECT, f"disconnect {bob.id}\n")
        bob.send(TICK, f"tick {bob.id}\n")
        bob.send(SHOOT, f"bulletPlayer {bob.id}\n")
        time.sleep(0.2)
        check(server.poll() is None, "server survives malformed and stale messages")
        carol = Player(port, "carol")
        try:
            carol.join()
            joined = True
        except AssertionError:
            joined = False
        check(joined, "a new player can still join after them")
    finally:
        server.terminate()
        try:
            _, errors = server.communicate(timeout=3)
        except subprocess.TimeoutExpired:
            server.kill()
            _, errors = server.communicate()

    check("Error sending data" not in errors, "server logs no send errors")
    print(f"\n{'FAILED' if failures else 'OK'}: {len(failures)} failure(s)")
    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main())
