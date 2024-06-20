Write-Host ""
Write-Host ">>> >>> Build Executable <<< <<<" -ForegroundColor Cyan
Write-Host ""

$startTime = Get-Date
& "C:\Users\desto\Scripts\projects\nodes_and_dots\shell\Build.ps1"
$endTime = Get-Date
$buildTime = $endTime - $startTime

Write-Host "Build .exe: $($buildTime.TotalSeconds) seconds"-ForegroundColor Cyan
Write-Host ""

Write-Host ">>> >>> Run Executable <<< <<<" -ForegroundColor Cyan
Write-Host ""

$startTime = Get-Date
& "C:\Users\desto\Scripts\projects\nodes_and_dots\shell\Run.ps1"
$endTime = Get-Date
$runTime = $endTime - $startTime

Write-Host "Run .exe: $($runTime.TotalSeconds) seconds"-ForegroundColor Cyan
Write-Host ""

Write-Host ">>> >>> Deps <<< <<<" -ForegroundColor Cyan
Write-Host ""

$startTime = Get-Date
& "C:\Users\desto\Scripts\projects\nodes_and_dots\shell\Deps.ps1"
$endTime = Get-Date
$depsTime = $endTime - $startTime

Write-Host "Deps: $($depsTime.TotalSeconds) seconds"-ForegroundColor Cyan
Write-Host ""

Write-Host ">>> >>> Clean Up <<< <<<" -ForegroundColor Cyan
Write-Host ""

$startTime = Get-Date
& "C:\Users\desto\Scripts\projects\nodes_and_dots\shell\Clean.ps1"
$endTime = Get-Date
$cleanTime = $endTime - $startTime

Write-Host "Clean Up: $($cleanTime.TotalSeconds) seconds"-ForegroundColor Cyan
Write-Host ""

Write-Host ">>> >>> Commit to GitHub <<< <<<" -ForegroundColor Cyan
Write-Host ""

$startTime = Get-Date
& "C:\Users\desto\Scripts\projects\nodes_and_dots\shell\Commit.ps1"
$endTime = Get-Date
$commitTime = $endTime - $startTime

Write-Host "Commit to GitHub: $($commitTime.TotalSeconds) seconds"-ForegroundColor Cyan
Write-Host ""

Write-Host ">>> >>> Program Completed <<< <<<" -ForegroundColor Green
Write-Host ""

