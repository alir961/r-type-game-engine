# R-Type

## Dependencies

- C++20 or later
- GNU Make
- CMake

## Installation

1. Clone repository

```shell
git clone git@github.com:EpitechPromo2026/B-CPP-500-LYN-5-2-rtype-timothe.medico.git
```

2. Install vcpkg (for Archlinux)

```shell
paru -S vcpkg
```

```shell
sudo gpasswd -a $USER vcpkg
```

3. Install dependencies

```shell
vcpkg install
```

> In case of permission issues: `sudo chown -R $USER:vcpkg /opt/vcpkg`

4. Prepare project compilation with cmake

```shell
cmake -S . -B build/out -DCMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake
```

5. Compile project with make

```shell
make -C build/out
```

> Binary paths:    
> `build/out/client/r-type_client`  
> `build/out/server/r-type_server`  

## Auteurs

| [<img src="https://github.com/alir961.png?size=85" width=85><br><sub>Ali RAAD</sub>](https://github.com/alir961) | [<img src="https://github.com/ArthurPcd.png?size=85" width=85><br><sub>Arthur PACAUD</sub>](https://github.com/ArthurPcd) | [<img src="https://github.com/Stickoman.png?size=85" width=85><br><sub>JumanJi Thomas</sub>](https://github.com/Stickoman) | [<img src="https://github.com/theoda74.png?size=85" width=85><br><sub>Théo D'AMORE</sub>](https://github.com/theoda74) | [<img src="https://github.com/Baragouin.png?size=85" width=85><br><sub>Timothé MEDICO</sub>](https://github.com/Baragouin) |   
|:------------------------------------------------------------------------------------------------------------------:|:---------------------------------------------------------------------------------------------------------------------:|:------------------------------------------------------------------------------------------------------------------------:|:----------------------------------------------------------------------------------------------------------------------:|:--------------------------------------------------------------------------------------------------------------------------:|
