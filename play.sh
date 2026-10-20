#!/usr/bin/env bash
# Launch R-Type. Build it first with ./install.sh
#
#   ./play.sh                  start a local server and one client (solo game)
#   ./play.sh 2                local server and two clients (multiplayer on one screen)
#   ./play.sh server [port] [easy|normal|hard]
#                              only the server, for other players to join (default: 4242, normal)
#   ./play.sh client           only a client, to join a server (address and port on the login screen)

set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SERVER="$ROOT/build/out/server/r-type_server"
CLIENT="$ROOT/build/out/client/r-type_client"
PORT=4242

# The binaries load their modules (build/out/engine/modules) and assets (client/assets)
# relative to the working directory, so always run from the repository root.
cd "$ROOT"

fail() { printf '\033[1;31merror:\033[0m %s\n' "$*" >&2; exit 1; }

[ -x "$SERVER" ] && [ -x "$CLIENT" ] || fail "R-Type is not built yet: run ./install.sh first"

start_server() {
    # A server from an earlier run is still up on this port: play on it instead of failing.
    if pgrep -f "$SERVER $1\$" >/dev/null; then
        echo "Using the server already running on port $1"
        return
    fi
    "$SERVER" "$1" > "$ROOT/build/server.log" 2>&1 &
    SERVER_PID=$!
    trap 'kill "$SERVER_PID" 2>/dev/null || true' EXIT INT TERM
    sleep 0.5
    kill -0 "$SERVER_PID" 2>/dev/null || fail "the server didn't start (port $1 already in use?), see build/server.log"
    echo "Server running on port $1 (log: build/server.log)"
}

MODE="${1:-1}"

case "$MODE" in
    server)
        echo "Server listening on UDP port ${2:-$PORT} (${3:-normal}). Players join with ./play.sh client"
        echo "Press Ctrl+C to stop it."
        exec "$SERVER" "${2:-$PORT}" ${3:+"$3"}
        ;;
    client)
        exec "$CLIENT"
        ;;
    [1-4])
        start_server "$PORT"
        echo "On the login screen, pick a username and press Enter (server: 127.0.0.1:$PORT)."
        pids=()
        for _ in $(seq "$MODE"); do
            "$CLIENT" > /dev/null 2>&1 &
            pids+=($!)
        done
        # The server stops when every client window is closed.
        wait "${pids[@]}"
        ;;
    -h|--help|help)
        sed -n '2,9p' "$0" | sed 's/^# \{0,1\}//'
        ;;
    *)
        fail "unknown option '$1' (see ./play.sh --help)"
        ;;
esac
