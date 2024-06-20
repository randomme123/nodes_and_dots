Write-Host ""
Write-Host ">>> >>> Build Executable <<< <<<"
Write-Host ""

$startTime = Get-Date
& "C:\Users\desto\Scripts\projects\nodes_and_dots\shell\Build.ps1"
$endTime = Get-Date
$buildTime = $endTime - $startTime

Write-Host "Time taken for Build .exe: $($buildTime.TotalSeconds) seconds"
Write-Host ""

Write-Host ">>> >>> Run Executable <<< <<<"
Write-Host ""

$startTime = Get-Date
& "C:\Users\desto\Scripts\projects\nodes_and_dots\shell\Run.ps1"
$endTime = Get-Date
$runTime = $endTime - $startTime

Write-Host "Time taken for Run .exe: $($runTime.TotalSeconds) seconds"
Write-Host ""

Write-Host ">>> >>> Deps <<< <<<"
Write-Host ""

$startTime = Get-Date
& "C:\Users\desto\Scripts\projects\nodes_and_dots\shell\Deps.ps1"
$endTime = Get-Date
$depsTime = $endTime - $startTime

Write-Host "Time taken for Deps: $($depsTime.TotalSeconds) seconds"
Write-Host ""

Write-Host ">>> >>> Clean Up <<< <<<"
Write-Host ""

$startTime = Get-Date
& "C:\Users\desto\Scripts\projects\nodes_and_dots\shell\Clean.ps1"
$endTime = Get-Date
$cleanTime = $endTime - $startTime

Write-Host "Time taken for Clean Up: $($cleanTime.TotalSeconds) seconds"
Write-Host ""

Write-Host ">>> >>> Commit to GitHub <<< <<<"
Write-Host ""

$startTime = Get-Date
& "C:\Users\desto\Scripts\projects\nodes_and_dots\shell\Commit.ps1"
$endTime = Get-Date
$commitTime = $endTime - $startTime

Write-Host "Time taken for Commit to GitHub: $($commitTime.TotalSeconds) seconds"
Write-Host ""

Write-Host ">>> >>> Program Completed <<< <<<"
Write-Host ""

