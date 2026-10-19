# R-Type — Networked Multiplayer Game Engine

A from-scratch C++20 game engine and multiplayer shoot'em up inspired by the classic *R-Type*: an authoritative UDP server, an Entity-Component-System shared by client and server, and runtime-loadable modules (graphics, sound, particles, animation, console).

> Team project (3 developers) — 3rd year at Epitech. See [My contribution](#my-contribution).

## Highlights

- **Client / server architecture** over a custom binary **UDP protocol** (Asio): server session manager, client network thread feeding a message queue to the game loop
- **Entity-Component-System** with an entity manager and component abstraction, plus an abstract factory for game entities
- **Pluggable engine modules** loaded and unloaded at runtime (`IModule`, `ModuleLoader`, `ModuleProvider`) — graphics, sound, particles, animation, console
- **Authoritative server game loop** at 60 ticks/s: movement, screen bounds, collisions, damage and score resolved on the server, then broadcast to clients
- **Gameplay**: several players per session, monsters, enemy starships that shoot back, static obstacles, health bars, score and a death screen
- **State-driven client UI**: login, menu, options, game, pause, win/lose views with reusable widgets (buttons, text/number inputs, checkboxes)
- Tooling: CMake + vcpkg, clang-format / clang-tidy, Doxygen documentation

## Architecture

```
engine/   Shared core: ECS, networking (UDPAdapter, NetworkMessage), module system, thread-safe tools
server/   Authoritative game server: UDPServer, SessionManager, GameLogic, EntityFactory
client/   Game client: UDPClient, view states, graphical entities, UI components, resource manager
tests/    GoogleTest unit tests for the ECS and engine tools (no SFML needed)
docs/     Protocol, packet format and ECS documentation
```

Design docs: [UDP protocol](docs/udpProtocol.md) · [Packet format](docs/packet.md) · [ECS](docs/ecs.md)

## Build

Requirements: C++20 compiler, CMake, [vcpkg](https://vcpkg.io) (SFML, Asio).

```bash
vcpkg install
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

Run:

```bash
./build/server/r-type_server
./build/client/r-type_client
```

## Tests

The engine core has unit tests (ECS components, entity manager, thread-safe queue, string and number utilities). They build on their own, without SFML or vcpkg:

```bash
cmake -S tests -B build/tests
cmake --build build/tests
ctest --test-dir build/tests --output-on-failure
```

CI builds the game and runs these tests on every push.

## My contribution

Main contributor by commit count (100+ commits). I designed and built:

- The **ECS** core (entity, component abstraction, entity manager) and the **entity abstract factory**
- The **graphical module** (sprite / text / shape rendering API) and the graphical-entity system with a resource manager for textures and audio
- The whole **client view-state system** (login, menu, options, game, pause, win/dead) and the UI component library
- Runtime **module loading / unloading from the options screen**
- Player / enemy concepts, health and score display, connection error handling, and the Doxygen documentation
- The engine unit tests (written later)

## Team

Ali Raad · Joan Thomas · Timothé Medico
