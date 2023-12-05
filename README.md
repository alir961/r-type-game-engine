# R-Type

## Prérequis

- C++20 ou version ultérieure
- GNU Make
- CMake
- VCPKG

## Installation

1. Clonez ce dépôt de code sur votre machine:

```shell
git clone git@github.com:EpitechPromo2026/B-CPP-500-LYN-5-2-rtype-timothe.medico.git
```

2. Installation de VCPKG

```shell
paru -S vcpkg
```

> En cas de problèmes de permission: `sudo chown -R $USER:vcpkg /opt/vcpkg`

3. Installation des dépendances

```shell
vcpkg install
```

4. Préparez la compilation du projet avec CMake

```shell
cmake -S . -B build/out -DCMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake
```

5. Compiler le projet via Makefile

```shell
make -C build/out
```

> Les binaires sont accessibles dans chemins suivants:  
> `build/out/client/r-type_client`
> `build/out/server/r-type_server`

## Auteurs

| [<img src="https://github.com/alir961.png?size=85" width=85><br><sub>Ali RAAD</sub>](https://github.com/ArthurPcd) | [<img src="https://github.com/ArthurPcd.png?size=85" width=85><br><sub>Arthur PACAUD</sub>](https://github.com/ArthurPcd) | [<img src="https://github.com/Stickoman.png?size=85" width=85><br><sub>JumanJi Thomas</sub>](https://github.com/Stickoman) | [<img src="https://github.com/theoda74.png?size=85" width=85><br><sub>Théo D'AMORE</sub>](https://github.com/theoda74) | [<img src="https://github.com/Baragouin.png?size=85" width=85><br><sub>Timothé MEDICO</sub>](https://github.com/Baragouin) |   
|:------------------------------------------------------------------------------------------------------------------:|:---------------------------------------------------------------------------------------------------------------------:|:------------------------------------------------------------------------------------------------------------------------:|:----------------------------------------------------------------------------------------------------------------------:|:--------------------------------------------------------------------------------------------------------------------------:|
