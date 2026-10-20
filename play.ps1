# Launch R-Type on Windows: the PowerShell twin of play.sh. Build it first with .\install.ps1
#
#   .\play.ps1                  start a local server and one client (solo game)
#   .\play.ps1 2                local server and two clients (multiplayer on one screen)
#   .\play.ps1 server [port] [easy|normal|hard]
#                               only the server, for other players to join (default: 4242, normal)
#   .\play.ps1 client           only a client, to join a server (address and port on the login screen)

param(
    [string]$Mode = '1',
    [string]$Port = '4242',
    [string]$Difficulty = ''
)

$ErrorActionPreference = 'Stop'
$Root = $PSScriptRoot
$Server = Join-Path $Root 'build\out\server\r-type_server.exe'
$Client = Join-Path $Root 'build\out\client\r-type_client.exe'

function Fail($message) { Write-Host "error: $message" -ForegroundColor Red; exit 1 }

# The binaries load their modules (build\out\engine\modules) and assets (client\assets)
# relative to the working directory, so always run from the repository root.
Set-Location $Root

if ($Mode -in @('-h', '--help', 'help')) {
    Get-Content $PSCommandPath | Select-Object -Skip 1 -First 6 | ForEach-Object { $_ -replace '^# ?', '' }
    exit 0
}
if (-not (Test-Path $Server) -or -not (Test-Path $Client)) { Fail 'R-Type is not built yet: run .\install.ps1 first' }

switch -Regex ($Mode) {
    '^server$' {
        Write-Host "Server listening on UDP port $Port ($(if ($Difficulty) { $Difficulty } else { 'normal' })). Players join with .\play.ps1 client"
        Write-Host 'Press Ctrl+C to stop it.'
        $serverArgs = @($Port) + @($Difficulty | Where-Object { $_ })
        & $Server @serverArgs
    }
    '^client$' {
        & $Client
    }
    '^[1-4]$' {
        $log = Join-Path $Root 'build\server.log'
        $serverProcess = Start-Process -FilePath $Server -ArgumentList $Port -WorkingDirectory $Root `
            -RedirectStandardOutput $log -RedirectStandardError "$log.err" -WindowStyle Hidden -PassThru
        Start-Sleep -Milliseconds 500
        if ($serverProcess.HasExited) { Fail "the server didn't start (port $Port already in use?), see build\server.log" }
        Write-Host "Server running on port $Port (log: build\server.log)"
        Write-Host "On the login screen, pick a username and press Enter (server: 127.0.0.1:$Port)."
        try {
            $clients = 1..[int]$Mode | ForEach-Object { Start-Process -FilePath $Client -WorkingDirectory $Root -PassThru }
            # The server stops when every client window is closed.
            $clients | Wait-Process
        } finally {
            Stop-Process -Id $serverProcess.Id -ErrorAction SilentlyContinue
        }
    }
    default {
        Fail "unknown option '$Mode' (see .\play.ps1 help)"
    }
}
