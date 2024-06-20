# Build exe
Write-Host ""
Write-Host ">>> >>> Build .exe <<< <<<"
Write-Host ""
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\build.ps1"

# Run exe
Write-Host ""
Write-Host ">>> >>> Run .exe <<< <<<"
Write-Host ""
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\run.ps1"

# deps
Write-Host ""
Write-Host ">>> >>> Deps <<< <<<"
Write-Host ""
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\deps.ps1"


# Clean up the build dir and docs
Write-Host ""
Write-Host ">>> >>> Clean Up <<< <<<"
Write-Host ""
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\clean.ps1"

# Commit to GitHub
Write-Host ""
Write-Host ">>> >>> Commit to GitHub <<< <<<"
Write-Host ""
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\commit.ps1"

# finish up
Write-Host ""
Write-Host ">>> >>> Program Completed <<< <<<"
Write-Host ""
