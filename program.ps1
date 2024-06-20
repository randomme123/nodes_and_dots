# Build exe
Write-Host ""
Write-Host ">>> >>> Build Executable <<< <<<"
Write-Host ""
$buildTime = Measure-Command {
    & "C:\Users\desto\Scripts\projects\nodes_and_dots\shell\Build.ps1"
}
Write-Host "Time taken for Build .exe: $($buildTime.TotalSeconds) seconds"
Write-Host ""


# Run exe
Write-Host ""
Write-Host ">>> >>> Run Executable <<< <<<"
Write-Host ""
$runTime = Measure-Command {
    & "C:\Users\desto\Scripts\projects\nodes_and_dots\shell\Run.ps1"
}
Write-Host "Time taken for Run .exe: $($runTime.TotalSeconds) seconds"
Write-Host ""


# Dependencies
Write-Host ""
Write-Host ">>> >>> Deps <<< <<<"
Write-Host ""
$depsTime = Measure-Command {
    & "C:\Users\desto\Scripts\projects\nodes_and_dots\shell\Deps.ps1"
}
Write-Host "Time taken for Deps: $($depsTime.TotalSeconds) seconds"
Write-Host ""


# Cleanup
Write-Host ""
Write-Host ">>> >>> Clean Up <<< <<<"
Write-Host ""
$cleanTime = Measure-Command {
    & "C:\Users\desto\Scripts\projects\nodes_and_dots\shell\Clean.ps1"
}
Write-Host "Time taken for Clean Up: $($cleanTime.TotalSeconds) seconds"
Write-Host ""


# Commit to github
Write-Host ""
Write-Host ">>> >>> Commit to GitHub <<< <<<"
Write-Host ""
$commitTime = Measure-Command {
    & "C:\Users\desto\Scripts\projects\nodes_and_dots\shell\Commit.ps1"
}
Write-Host "Time taken for Commit to GitHub: $($commitTime.TotalSeconds) seconds"
Write-Host ""


# finish
Write-Host ""
Write-Host ">>> >>> Program Completed <<< <<<"
Write-Host ""
