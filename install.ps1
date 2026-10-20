# Build R-Type on Windows: the PowerShell twin of install.sh.
#
#   .\install.ps1            check the tools, set up vcpkg, build into build\out
#
# Needs Visual Studio 2022 (or its Build Tools) with the "Desktop development with C++" workload, and git.
# vcpkg builds SFML and Asio; CMake comes with Visual Studio (or is downloaded by vcpkg).

$ErrorActionPreference = 'Stop'
$Root = $PSScriptRoot
$BuildDir = Join-Path $Root 'build\out'

function Info($message) { Write-Host "==> $message" -ForegroundColor Cyan }
function Fail($message) { Write-Host "error: $message" -ForegroundColor Red; exit 1 }

if (-not (Get-Command git -ErrorAction SilentlyContinue)) {
    Fail 'git is missing: winget install Git.Git'
}
$vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
if (-not (Test-Path $vswhere) -or -not (& $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath)) {
    Fail 'Visual Studio 2022 with the C++ tools is missing: winget install Microsoft.VisualStudio.2022.BuildTools --override "--add Microsoft.VisualStudio.Workload.VCTools --includeRecommended --passive"'
}

# Reuse an existing vcpkg ($env:VCPKG_ROOT, the one preinstalled on GitHub runners, or ~\vcpkg),
# otherwise clone one next to the project.
$candidates = @($env:VCPKG_ROOT, $env:VCPKG_INSTALLATION_ROOT, (Join-Path $HOME 'vcpkg')) | Where-Object { $_ }
$Vcpkg = $candidates | Where-Object { Test-Path (Join-Path $_ 'vcpkg.exe') } | Select-Object -First 1
if (-not $Vcpkg) {
    $Vcpkg = Join-Path $Root 'vcpkg'
    Info "Setting up vcpkg in $Vcpkg"
    if (-not (Test-Path (Join-Path $Vcpkg '.git'))) { git clone https://github.com/microsoft/vcpkg.git $Vcpkg }
    & (Join-Path $Vcpkg 'bootstrap-vcpkg.bat') -disableMetrics
    if ($LASTEXITCODE -ne 0) { Fail 'vcpkg bootstrap failed' }
}
Info "Using vcpkg: $Vcpkg"

# vcpkg.json pins a baseline commit: make sure this vcpkg checkout has it.
$baseline = (Get-Content (Join-Path $Root 'vcpkg.json') -Raw | ConvertFrom-Json).'builtin-baseline'
git -C $Vcpkg cat-file -e "$baseline^{commit}" 2>$null
if ($LASTEXITCODE -ne 0) {
    Info 'Fetching the vcpkg baseline'
    git -C $Vcpkg fetch --quiet origin
}

$cmake = Get-Command cmake -ErrorAction SilentlyContinue
if ($cmake) {
    $Cmake = $cmake.Source
} else {
    Info 'cmake not found, using the one vcpkg downloads'
    $Cmake = (& (Join-Path $Vcpkg 'vcpkg.exe') fetch cmake | Select-Object -Last 1)
}

Info 'Configuring (the first run builds SFML and its dependencies: several minutes)'
$env:VCPKG_ROOT = $Vcpkg
# Static SFML like on Linux, with the shared C runtime so the game and its module DLLs share one heap
# (triplets\x64-windows-static-md-release.cmake: release packages only, the game is built in Release).
& $Cmake -S $Root -B $BuildDir `
    -DCMAKE_TOOLCHAIN_FILE="$Vcpkg\scripts\buildsystems\vcpkg.cmake" `
    -DVCPKG_OVERLAY_TRIPLETS="$Root\triplets" `
    -DVCPKG_TARGET_TRIPLET=x64-windows-static-md-release
if ($LASTEXITCODE -ne 0) { Fail 'CMake configuration failed' }

Info 'Building'
& $Cmake --build $BuildDir --config Release --parallel
if ($LASTEXITCODE -ne 0) { Fail 'build failed' }

Write-Host ''
Write-Host 'R-Type is built.' -ForegroundColor Green
Write-Host 'Play locally:        .\play.ps1'
Write-Host 'Host a game:         .\play.ps1 server 4242'
Write-Host 'Join a game:         .\play.ps1 client'
