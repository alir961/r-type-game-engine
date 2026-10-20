# x64-windows-static-md, release only: static SFML (as on Linux) with the shared C runtime,
# and no debug packages that a Release build of the game could link by mistake.
set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE static)
set(VCPKG_BUILD_TYPE release)
