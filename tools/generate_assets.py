#!/usr/bin/env python3
"""Generate the client's sprite sheets, parallax backgrounds and sounds.

All art is drawn procedurally (Pillow only), so it is original and reproducible:

    python3 tools/generate_assets.py

Frame sizes match the collision rectangles sent by the server
(server/include/game/EntityFactory.hpp), and frame offsets match the
animation classes in engine/modules/animation/entity/.
"""

import math
import random
import struct
import wave
from pathlib import Path

from PIL import Image, ImageChops, ImageDraw, ImageFilter

ROOT = Path(__file__).resolve().parent.parent
SPRITES = ROOT / "client" / "assets" / "sprites"
BACKGROUNDS = ROOT / "client" / "assets" / "background"
SOUNDS = ROOT / "client" / "assets" / "sounds"

OUTLINE = (10, 12, 28, 255)
TRANSPARENT = (0, 0, 0, 0)


# --------------------------------------------------------------------------- helpers

def shade(color, factor):
    """Lighten (factor > 1) or darken (factor < 1) an RGB(A) color."""
    r, g, b = color[:3]
    if factor >= 1:
        k = factor - 1
        r, g, b = (int(c + (255 - c) * k) for c in (r, g, b))
    else:
        r, g, b = (int(c * factor) for c in (r, g, b))
    return (r, g, b, color[3] if len(color) == 4 else 255)


def outline(img, color=OUTLINE):
    """Add a 1px outline around every opaque pixel (pixel-art style)."""
    alpha = img.getchannel("A").point(lambda a: 255 if a > 40 else 0)
    grown = alpha.filter(ImageFilter.MaxFilter(3))
    ring = ImageChops.subtract(grown, alpha)
    base = Image.new("RGBA", img.size, TRANSPARENT)
    base.paste(Image.new("RGBA", img.size, color), mask=ring)
    base.alpha_composite(img)
    return base


def glow(img, radius, strength=1.0):
    """Soft additive glow under the sprite, used for energy shots and flames."""
    halo = img.filter(ImageFilter.GaussianBlur(radius))
    if strength != 1.0:
        a = halo.getchannel("A").point(lambda v: min(255, int(v * strength)))
        halo.putalpha(a)
    halo.alpha_composite(img)
    return halo


def sheet(frames, columns=None):
    columns = columns or len(frames)
    w, h = frames[0].size
    rows = math.ceil(len(frames) / columns)
    out = Image.new("RGBA", (w * columns, h * rows), TRANSPARENT)
    for i, frame in enumerate(frames):
        out.paste(frame, ((i % columns) * w, (i // columns) * h))
    return out


# --------------------------------------------------------------------------- player ship (33x15)

PLAYER_COLORS = {
    "turquoise": (40, 210, 200),
    "purple": (170, 90, 240),
    "green": (90, 220, 90),
    "red": (240, 70, 80),
    "blue": (70, 130, 250),
}
PLAYER_FRAMES = 4


def player_frame(accent, frame):
    w, h = 33, 15
    img = Image.new("RGBA", (w, h), TRANSPARENT)
    d = ImageDraw.Draw(img)
    hull = (196, 204, 222)

    # Engine flame (behind the hull), flickering length.
    flame_len = [6, 8, 5, 7][frame]
    d.polygon([(6, 5), (6 - flame_len, 7), (6, 9)], fill=(255, 150, 40, 255))
    d.polygon([(6, 6), (6 - flame_len + 3, 7), (6, 8)], fill=(255, 240, 160, 255))

    # Wings (accent color).
    d.polygon([(9, 5), (14, 1), (19, 1), (18, 5)], fill=shade(accent, 1.0))
    d.polygon([(9, 9), (14, 13), (19, 13), (18, 9)], fill=shade(accent, 0.7))
    d.line([(14, 1), (19, 1)], fill=shade(accent, 1.4))

    # Hull: top half lit, bottom half shaded.
    d.polygon([(5, 4), (20, 3), (28, 5), (32, 7), (28, 9), (20, 11), (5, 10)], fill=hull)
    d.polygon([(5, 7), (32, 7), (28, 9), (20, 11), (5, 10)], fill=shade(hull, 0.72))
    d.line([(7, 4), (20, 3), (27, 5)], fill=shade(hull, 1.5))
    # Accent stripe and nose tip.
    d.line([(8, 7), (22, 7)], fill=accent)
    d.point((31, 7), fill=shade(accent, 1.4))
    # Cockpit.
    d.ellipse([(19, 4), (26, 7)], fill=(30, 50, 90, 255))
    d.line([(21, 5), (24, 5)], fill=(150, 230, 255, 255))
    # Engine nozzle.
    d.rectangle([(4, 5), (6, 9)], fill=(80, 86, 104, 255))
    return outline(img)


def player_sheet():
    frames = []
    for accent in PLAYER_COLORS.values():
        frames += [player_frame(accent, f) for f in range(PLAYER_FRAMES)]
    return sheet(frames, PLAYER_FRAMES)


# --------------------------------------------------------------------------- player shot (14x14)

def player_bullet_frame(frame):
    img = Image.new("RGBA", (14, 14), TRANSPARENT)
    d = ImageDraw.Draw(img)
    pulse = [0, 1, 2, 1][frame]
    d.ellipse([(1, 5 - pulse // 2), (13, 8 + pulse // 2)], fill=(40, 200, 255, 200))
    d.ellipse([(4, 6), (13, 7 + (pulse > 0))], fill=(160, 240, 255, 255))
    d.line([(7, 6), (12, 6)], fill=(255, 255, 255, 255))
    return glow(img, 1.2, 1.4)


# --------------------------------------------------------------------------- monster (33x33)

def monster_frame(frame):
    img = Image.new("RGBA", (33, 33), TRANSPARENT)
    d = ImageDraw.Draw(img)
    body = (150, 60, 180)
    phase = frame / 4 * 2 * math.pi

    # Tentacles trailing to the right, waving.
    for i, base_y in enumerate((10, 16, 22)):
        points = []
        for step in range(9):
            x = 20 + step * 1.5
            y = base_y + math.sin(phase + step * 0.7 + i) * (1 + step * 0.35)
            points.append((x, y))
        d.line(points, fill=shade(body, 0.75), width=3 - (i == 1))
        d.point(points[-1], fill=(255, 120, 200, 255))

    # Body with spikes.
    d.ellipse([(5, 6), (25, 26)], fill=body)
    d.pieslice([(5, 6), (25, 26)], 200, 340, fill=shade(body, 1.3))
    d.pieslice([(5, 6), (25, 26)], 20, 160, fill=shade(body, 0.7))
    for angle in range(0, 360, 45):
        rad = math.radians(angle + frame * 4)
        x0, y0 = 15 + math.cos(rad) * 10, 16 + math.sin(rad) * 10
        x1, y1 = 15 + math.cos(rad) * 13, 16 + math.sin(rad) * 13
        d.line([(x0, y0), (x1, y1)], fill=shade(body, 1.1), width=2)

    # Big eye looking at the player (left), blinking on the last frame.
    if frame == 3:
        d.line([(8, 16), (18, 16)], fill=(40, 10, 40, 255), width=2)
    else:
        d.ellipse([(7, 11), (19, 21)], fill=(250, 245, 230, 255))
        d.ellipse([(8, 13), (14, 19)], fill=(230, 30, 50, 255))
        d.ellipse([(9, 15), (11, 17)], fill=(20, 0, 10, 255))
        d.point((10, 14), fill=(255, 255, 255, 255))
    return outline(img)


# --------------------------------------------------------------------------- space mine obstacle (122x122)

def mine_frame(frame, frames=8):
    size = 122
    img = Image.new("RGBA", (size, size), TRANSPARENT)
    d = ImageDraw.Draw(img)
    c = size / 2
    metal = (110, 118, 138)
    # 8 spikes; rotating by 45/frames degrees per frame keeps the loop seamless.
    rotation = math.radians(frame * 45 / frames)
    for k in range(8):
        a = rotation + k * math.pi / 4
        tip = (c + math.cos(a) * 58, c + math.sin(a) * 58)
        left = (c + math.cos(a - 0.22) * 34, c + math.sin(a - 0.22) * 34)
        right = (c + math.cos(a + 0.22) * 34, c + math.sin(a + 0.22) * 34)
        d.polygon([left, tip, right], fill=shade(metal, 0.8))
        d.line([left, tip], fill=shade(metal, 1.3), width=2)
        d.ellipse([(tip[0] - 3, tip[1] - 3), (tip[0] + 3, tip[1] + 3)], fill=(220, 60, 60, 255))
    # Core sphere with shading.
    d.ellipse([(c - 36, c - 36), (c + 36, c + 36)], fill=shade(metal, 0.6))
    d.ellipse([(c - 34, c - 36), (c + 30, c + 28)], fill=metal)
    d.ellipse([(c - 26, c - 30), (c + 2, c - 8)], fill=shade(metal, 1.35))
    # Rivets around the core.
    for k in range(12):
        a = rotation + k * math.pi / 6
        x, y = c + math.cos(a) * 30, c + math.sin(a) * 30
        d.ellipse([(x - 2, y - 2), (x + 2, y + 2)], fill=shade(metal, 0.5))
    # Pulsing warning light.
    pulse = (math.sin(frame / frames * 2 * math.pi) + 1) / 2
    r = 9 + pulse * 4
    light = Image.new("RGBA", (size, size), TRANSPARENT)
    ImageDraw.Draw(light).ellipse([(c - r, c - r), (c + r, c + r)], fill=(255, 60, 40, int(160 + 95 * pulse)))
    light = glow(light, 6, 1.5)
    img.alpha_composite(light)
    d = ImageDraw.Draw(img)
    d.ellipse([(c - 4, c - 4), (c + 4, c + 4)], fill=(255, 230, 200, 255))
    return outline(img)


# --------------------------------------------------------------------------- enemy fighter (32x22), faces left

def starship_frame(frame):
    img = Image.new("RGBA", (32, 22), TRANSPARENT)
    d = ImageDraw.Draw(img)
    hull = (200, 70, 60)

    flame = [5, 7, 4, 6][frame]
    for y in (6, 15):
        d.polygon([(27, y - 2), (27 + flame, y), (27, y + 2)], fill=(120, 200, 255, 255))
        d.line([(27, y), (27 + flame - 2, y)], fill=(230, 250, 255, 255))

    # Swept wings.
    d.polygon([(10, 9), (22, 0), (28, 0), (24, 9)], fill=shade(hull, 0.8))
    d.polygon([(10, 12), (22, 21), (28, 21), (24, 12)], fill=shade(hull, 0.6))
    # Engine pods.
    d.rectangle([(20, 4), (27, 8)], fill=(90, 90, 110, 255))
    d.rectangle([(20, 13), (27, 17)], fill=(70, 70, 90, 255))
    # Fuselage, pointing left.
    d.polygon([(1, 11), (8, 7), (26, 7), (26, 14), (8, 14)], fill=hull)
    d.polygon([(1, 11), (26, 11), (26, 14), (8, 14)], fill=shade(hull, 0.7))
    d.line([(8, 7), (25, 7)], fill=shade(hull, 1.4))
    # Canopy.
    d.ellipse([(7, 8), (14, 11)], fill=(255, 210, 60, 255))
    d.point((9, 9), fill=(255, 255, 220, 255))
    # Gun barrel.
    d.line([(0, 11), (4, 11)], fill=(60, 60, 70, 255))
    return outline(img)


# --------------------------------------------------------------------------- enemy shot (32x28), moves left

def enemy_bullet_frame(frame):
    img = Image.new("RGBA", (32, 28), TRANSPARENT)
    d = ImageDraw.Draw(img)
    cx, cy = 10, 14
    # Tail to the right.
    tail = [12, 15, 11, 14][frame]
    d.polygon([(cx, cy - 6), (cx + tail + 6, cy), (cx, cy + 6)], fill=(255, 90, 30, 140))
    d.polygon([(cx, cy - 3), (cx + tail, cy), (cx, cy + 3)], fill=(255, 190, 60, 200))
    r = [7, 8, 7, 6][frame]
    d.ellipse([(cx - r, cy - r), (cx + r, cy + r)], fill=(255, 60, 40, 255))
    d.ellipse([(cx - r + 3, cy - r + 3), (cx + r - 3, cy + r - 3)], fill=(255, 200, 90, 255))
    d.ellipse([(cx - 2, cy - 2), (cx + 2, cy + 2)], fill=(255, 255, 230, 255))
    return glow(img, 2, 1.3)


# --------------------------------------------------------------------------- explosion (48x48)

def explosion_frame(frame, frames=7):
    size = 48
    img = Image.new("RGBA", (size, size), TRANSPARENT)
    d = ImageDraw.Draw(img)
    c = size / 2
    t = frame / (frames - 1)
    rng = random.Random(7)
    # Fireball grows then fades.
    r = 6 + t * 16
    fade = int(255 * (1 - t) ** 0.8)
    d.ellipse([(c - r, c - r), (c + r, c + r)], fill=(255, 90, 30, fade))
    inner = r * (1 - t) * 0.8
    if inner > 1:
        d.ellipse([(c - inner, c - inner), (c + inner, c + inner)], fill=(255, 220, 120, 255))
    if t < 0.4:
        d.ellipse([(c - 3, c - 3), (c + 3, c + 3)], fill=(255, 255, 255, 255))
    # Shock ring.
    ring = 8 + t * 20
    d.ellipse([(c - ring, c - ring), (c + ring, c + ring)], outline=(255, 200, 120, fade), width=2)
    # Debris sparks flying out.
    for _ in range(10):
        a = rng.uniform(0, 2 * math.pi)
        dist = rng.uniform(6, 22) * (0.3 + t)
        x, y = c + math.cos(a) * dist, c + math.sin(a) * dist
        d.rectangle([(x, y), (x + 1, y + 1)], fill=(255, 230, 150, fade))
    return glow(img, 2)


# --------------------------------------------------------------------------- backgrounds (576x324, tile horizontally)

BG_W, BG_H = 576, 324


def stars_layer(seed, count, sizes, alpha_range, tint=(255, 255, 255)):
    rng = random.Random(seed)
    img = Image.new("RGBA", (BG_W, BG_H), TRANSPARENT)
    d = ImageDraw.Draw(img)
    for _ in range(count):
        x, y = rng.randrange(BG_W), rng.randrange(BG_H)
        size = rng.choice(sizes)
        a = rng.randint(*alpha_range)
        color = tuple(min(255, int(c * rng.uniform(0.85, 1.0))) for c in tint) + (a,)
        if size == 1:
            d.point((x, y), fill=color)
        else:
            d.rectangle([(x, y), (x + size - 1, y + size - 1)], fill=color)
            if size >= 2 and a > 200:
                # Small cross sparkle on the brightest stars.
                d.point([(x - 1, y), (x + size, y), (x, y - 1), (x, y + size)], fill=color[:3] + (a // 3,))
    return img


def background_base():
    """Opaque far layer: vertical gradient plus soft nebula clouds that wrap horizontally."""
    img = Image.new("RGBA", (BG_W, BG_H))
    d = ImageDraw.Draw(img)
    top, bottom = (6, 8, 22), (18, 16, 44)
    for y in range(BG_H):
        t = y / (BG_H - 1)
        d.line([(0, y), (BG_W, y)], fill=tuple(int(a + (b - a) * t) for a, b in zip(top, bottom)) + (255,))
    nebula = Image.new("RGBA", (BG_W, BG_H), TRANSPARENT)
    nd = ImageDraw.Draw(nebula)
    rng = random.Random(3)
    for color, count in (((110, 40, 150), 14), ((30, 90, 160), 12), ((160, 50, 90), 6)):
        for _ in range(count):
            x, y = rng.randrange(BG_W), rng.randrange(40, BG_H - 40)
            rx, ry = rng.randint(30, 90), rng.randint(20, 50)
            for dx in (-BG_W, 0, BG_W):  # draw wrapped copies so the tile is seamless
                nd.ellipse([(x + dx - rx, y - ry), (x + dx + rx, y + ry)], fill=color + (38,))
    nebula = nebula.filter(ImageFilter.GaussianBlur(18))
    img.alpha_composite(nebula)
    img.alpha_composite(stars_layer(11, 260, [1], (40, 120)))
    return img


def planet_layer():
    img = stars_layer(21, 90, [1], (90, 170), (200, 210, 255))
    cx, cy, r = 430, 250, 46
    disc = Image.new("L", (BG_W, BG_H), 0)
    ImageDraw.Draw(disc).ellipse([(cx - r, cy - r), (cx + r, cy + r)], fill=255)

    surface = Image.new("RGBA", (BG_W, BG_H), (60, 80, 150, 255))
    d = ImageDraw.Draw(surface)
    for i, band in enumerate(range(-r + 6, r, 12)):
        d.line([(cx - r, cy + band), (cx + r, cy + band + 5)], fill=(78 + i * 7, 100 + i * 3, 178, 255), width=5)
    # Night side: a dark disc offset to the lower right, kept inside the planet.
    d.ellipse([(cx - r + 18, cy - r + 6), (cx + r + 30, cy + r + 24)], fill=(14, 16, 40, 255))
    surface = surface.filter(ImageFilter.GaussianBlur(1.5))

    planet = Image.new("RGBA", (BG_W, BG_H), TRANSPARENT)
    d = ImageDraw.Draw(planet)
    d.ellipse([(cx - r - 5, cy - r - 5), (cx + r + 5, cy + r + 5)], fill=(90, 140, 255, 45))
    planet = planet.filter(ImageFilter.GaussianBlur(4))
    planet.paste(surface, mask=disc)
    d = ImageDraw.Draw(planet)
    d.arc([(cx - r - 28, cy - 9), (cx + r + 28, cy + 9)], 0, 180, fill=(170, 180, 230, 170), width=2)
    img.alpha_composite(planet)
    return img


def near_stars_layer():
    img = stars_layer(31, 60, [1, 2], (150, 230), (220, 230, 255))
    return img


def streak_layer():
    """Fastest layer: few bright stars and speed streaks to sell the motion."""
    rng = random.Random(41)
    img = stars_layer(43, 22, [2, 3], (200, 255))
    d = ImageDraw.Draw(img)
    for _ in range(14):
        x, y = rng.randrange(BG_W), rng.randrange(BG_H)
        length = rng.randint(14, 40)
        for i in range(length):
            a = int(110 * (1 - i / length))
            d.point(((x + i) % BG_W, y), fill=(170, 210, 255, a))
    return img


# --------------------------------------------------------------------------- sounds (mono 16-bit WAV)

RATE = 22050


def write_wav(path, samples):
    peak = max(1e-9, max(abs(v) for v in samples))
    scale = 0.9 / peak if peak > 0.9 else 1.0
    with wave.open(str(path), "wb") as out:
        out.setnchannels(1)
        out.setsampwidth(2)
        out.setframerate(RATE)
        out.writeframes(b"".join(struct.pack("<h", int(max(-1.0, min(1.0, v * scale)) * 32767)) for v in samples))


def envelope(i, n, attack=0.005, curve=3.0):
    t = i / n
    a = min(1.0, i / max(1, attack * RATE))
    return a * (1 - t) ** curve


def sweep(duration, f_start, f_end, wave_shape="square", curve=2.0, volume=0.6):
    n = int(duration * RATE)
    phase, out = 0.0, []
    for i in range(n):
        freq = f_start + (f_end - f_start) * (i / n)
        phase += freq / RATE
        if wave_shape == "square":
            value = 1.0 if (phase % 1.0) < 0.5 else -1.0
        elif wave_shape == "saw":
            value = 2 * (phase % 1.0) - 1
        else:
            value = math.sin(2 * math.pi * phase)
        out.append(value * envelope(i, n, curve=curve) * volume)
    return out


def noise(duration, seed, smooth=1, curve=2.0, volume=0.8):
    rng = random.Random(seed)
    n = int(duration * RATE)
    raw = [rng.uniform(-1, 1) for _ in range(n)]
    out, acc = [], 0.0
    for i, v in enumerate(raw):
        # Smoothing factor grows over time: the blast gets duller as it fades.
        k = 1.0 / (smooth + i / n * smooth * 3)
        acc += (v - acc) * k
        out.append(acc * envelope(i, n, curve=curve) * volume)
    return out


def mix(*tracks):
    n = max(len(t) for t in tracks)
    return [sum(t[i] for t in tracks if i < len(t)) for i in range(n)]


def note_freq(semitone_from_a4):
    return 440.0 * 2 ** (semitone_from_a4 / 12)


def music_loop():
    """16-second synthwave loop (A minor, 120 BPM): bass, arpeggio and hi-hats."""
    bpm, bars = 120, 8
    beat = 60 / bpm
    n = int(bars * 4 * beat * RATE)
    out = [0.0] * n
    rng = random.Random(5)
    progression = [0, 0, -4, -4, -7, -7, -2, -2]   # Am, F, D... as offsets from A
    for bar, root in enumerate(progression):
        bar_start = bar * 4 * beat
        # Bass: eighth notes on the root, octave jumps on the off-beats.
        for step in range(8):
            start = int((bar_start + step * beat / 2) * RATE)
            freq = note_freq(root - 24 + (12 if step % 2 else 0))
            length = int(beat / 2 * RATE * 0.9)
            phase = 0.0
            for i in range(length):
                if start + i >= n:
                    break
                phase += freq / RATE
                saw = 2 * (phase % 1.0) - 1
                out[start + i] += saw * 0.22 * (1 - i / length) ** 1.5
        # Arpeggio: minor triad in sixteenths.
        chord = [root, root + 3, root + 7, root + 12]
        for step in range(16):
            start = int((bar_start + step * beat / 4) * RATE)
            freq = note_freq(chord[step % 4])
            length = int(beat / 4 * RATE)
            phase = 0.0
            for i in range(length):
                if start + i >= n:
                    break
                phase += freq / RATE
                square = 1.0 if (phase % 1.0) < 0.25 else -1.0
                out[start + i] += square * 0.07 * (1 - i / length) ** 2
        # Hi-hats on every eighth, kick on each beat.
        for step in range(8):
            start = int((bar_start + step * beat / 2) * RATE)
            for i in range(int(0.04 * RATE)):
                if start + i < n:
                    out[start + i] += rng.uniform(-1, 1) * 0.05 * (1 - i / (0.04 * RATE)) ** 2
        for step in range(4):
            start = int((bar_start + step * beat) * RATE)
            length = int(0.18 * RATE)
            phase = 0.0
            for i in range(length):
                if start + i < n:
                    phase += (110 - 70 * i / length) / RATE
                    out[start + i] += math.sin(2 * math.pi * phase) * 0.35 * (1 - i / length) ** 2
    return out


def sounds():
    return {
        "shoot": sweep(0.11, 1400, 500, "square", curve=2.5, volume=0.35),
        "enemy_shoot": mix(sweep(0.22, 420, 140, "saw", curve=2.0, volume=0.35), noise(0.22, 2, smooth=4, volume=0.2)),
        "explosion": mix(noise(0.7, 3, smooth=3, curve=2.2, volume=1.0), sweep(0.5, 120, 40, "sine", curve=2.0, volume=0.6)),
        "hit": mix(noise(0.14, 4, smooth=2, curve=2.5, volume=0.7), sweep(0.14, 220, 90, "sine", curve=2.0, volume=0.6)),
        "ui_move": sweep(0.05, 880, 880, "square", curve=3.0, volume=0.2),
        "ui_select": sweep(0.06, 660, 660, "square", volume=0.25) + sweep(0.09, 990, 990, "square", volume=0.25),
        "game_over": sum((sweep(0.22, note_freq(n), note_freq(n), "square", curve=1.5, volume=0.3) for n in (7, 3, 0, -5)), []),
        "music": music_loop(),
    }


# --------------------------------------------------------------------------- main

def main():
    SPRITES.mkdir(parents=True, exist_ok=True)
    BACKGROUNDS.mkdir(parents=True, exist_ok=True)

    outputs = {
        SPRITES / "player.png": player_sheet(),
        SPRITES / "player_bullet.png": sheet([player_bullet_frame(f) for f in range(4)]),
        SPRITES / "monster.png": sheet([monster_frame(f) for f in range(4)]),
        SPRITES / "mine.png": sheet([mine_frame(f) for f in range(8)]),
        SPRITES / "enemy_starship.png": sheet([starship_frame(f) for f in range(4)]),
        SPRITES / "enemy_bullet.png": sheet([enemy_bullet_frame(f) for f in range(4)]),
        SPRITES / "explosion.png": sheet([explosion_frame(f) for f in range(7)]),
        BACKGROUNDS / "1.png": background_base(),
        BACKGROUNDS / "2.png": planet_layer(),
        BACKGROUNDS / "3.png": near_stars_layer(),
        BACKGROUNDS / "4.png": streak_layer(),
    }
    for path, image in outputs.items():
        image.save(path, optimize=True)
        print(f"wrote {path.relative_to(ROOT)} {image.size[0]}x{image.size[1]}")

    SOUNDS.mkdir(parents=True, exist_ok=True)
    for name, samples in sounds().items():
        path = SOUNDS / f"{name}.wav"
        write_wav(path, samples)
        print(f"wrote {path.relative_to(ROOT)} {len(samples) / RATE:.2f}s")


if __name__ == "__main__":
    main()
