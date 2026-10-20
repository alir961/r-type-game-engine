#!/usr/bin/env bash
# Build R-Type (server, client and engine modules) into build/out.
#
#   ./install.sh            check dependencies, set up vcpkg, build
#   ./install.sh --deps     same, but first install the system packages (asks for sudo)
#
# Then start the game with ./play.sh

set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$ROOT/build/out"
cd "$ROOT"

bold() { printf '\033[1m%s\033[0m\n' "$*"; }
info() { printf '\033[1;36m==>\033[0m %s\n' "$*"; }
fail() { printf '\033[1;31merror:\033[0m %s\n' "$*" >&2; exit 1; }

# ---------------------------------------------------------------- system packages

# Everything vcpkg can't build itself: a compiler, the tools vcpkg needs,
# and the X11/OpenGL/udev headers SFML's window module links against.
deps_command() {
    if command -v apt-get >/dev/null; then
        echo "sudo apt-get update && sudo apt-get install -y build-essential git curl zip unzip tar pkg-config cmake libx11-dev libxrandr-dev libxcursor-dev libxi-dev libudev-dev libgl1-mesa-dev"
    elif command -v pacman >/dev/null; then
        echo "sudo pacman -S --needed base-devel git curl zip unzip tar pkgconf cmake libx11 libxrandr libxcursor libxi systemd-libs mesa"
    elif command -v dnf >/dev/null; then
        echo "sudo dnf install -y gcc-c++ make git curl zip unzip tar pkgconf cmake libX11-devel libXrandr-devel libXcursor-devel libXi-devel systemd-devel mesa-libGL-devel"
    fi
}

missing_deps() {
    local missing=()

    for tool in g++ make git curl zip unzip tar pkg-config; do
        command -v "$tool" >/dev/null || missing+=("$tool")
    done
    for header in X11/Xlib.h X11/extensions/Xrandr.h X11/Xcursor/Xcursor.h X11/extensions/XInput2.h libudev.h GL/gl.h; do
        [ -f "/usr/include/$header" ] || missing+=("$header")
    done
    echo "${missing[*]}"
}

if [ "${1:-}" = "--deps" ]; then
    cmd="$(deps_command)"
    [ -n "$cmd" ] || fail "unknown package manager: install the packages listed in the README by hand"
    info "Installing system packages"
    eval "$cmd"
fi

missing="$(missing_deps)"
if [ -n "$missing" ]; then
    printf '\033[1;31merror:\033[0m missing system dependencies: %s\n\n' "$missing" >&2
    cmd="$(deps_command)"
    if [ -n "$cmd" ]; then
        echo "Install them with:" >&2
        echo "    $cmd" >&2
        echo "or run: ./install.sh --deps" >&2
    fi
    exit 1
fi

# ---------------------------------------------------------------- vcpkg

# Reuse an existing vcpkg ($VCPKG_ROOT or ~/vcpkg), otherwise clone one next to the project.
if [ -n "${VCPKG_ROOT:-}" ] && [ -x "$VCPKG_ROOT/vcpkg" ]; then
    VCPKG="$VCPKG_ROOT"
elif [ -x "$HOME/vcpkg/vcpkg" ]; then
    VCPKG="$HOME/vcpkg"
else
    VCPKG="$ROOT/vcpkg"
    if [ ! -x "$VCPKG/vcpkg" ]; then
        info "Setting up vcpkg in $VCPKG"
        [ -d "$VCPKG/.git" ] || git clone https://github.com/microsoft/vcpkg.git "$VCPKG"
        "$VCPKG/bootstrap-vcpkg.sh" -disableMetrics
    fi
fi
info "Using vcpkg: $VCPKG"

# vcpkg's manifest pins SFML 2.6 to an older baseline: make sure this clone knows that commit.
if ! git -C "$VCPKG" cat-file -e "$(sed -n 's/.*"builtin-baseline": "\([0-9a-f]*\)".*/\1/p' vcpkg.json)^{commit}" 2>/dev/null; then
    info "Updating vcpkg to know the pinned baseline"
    git -C "$VCPKG" fetch --quiet origin
fi

# ---------------------------------------------------------------- build

if command -v cmake >/dev/null; then
    CMAKE=cmake
else
    info "cmake not found, using the one vcpkg downloads"
    CMAKE="$("$VCPKG/vcpkg" fetch cmake | tail -n 1)"
fi

info "Configuring (the first run builds SFML and its dependencies: a few minutes)"
VCPKG_ROOT="$VCPKG" "$CMAKE" -S . -B "$BUILD_DIR" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_TOOLCHAIN_FILE="$VCPKG/scripts/buildsystems/vcpkg.cmake"

info "Building"
"$CMAKE" --build "$BUILD_DIR" -j "$(nproc)"

echo
bold "R-Type is built."
echo "Play locally:        ./play.sh"
echo "Host a game:         ./play.sh server 4242"
echo "Join a game:         ./play.sh client"
