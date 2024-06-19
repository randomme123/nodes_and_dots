# build exe
Write-Host ""
Write-Host "Build .exe."

& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\build.ps1"

Write-Host ""
Write-Host "Run .exe."

# Run the application
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\run.ps1"

Write-Host ""
Write-Host "Clean Up."

# Clean up the build directory
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\clean.ps1"

Write-Host ""
Write-Host "Start SSH Service."

# start ssh service
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\sshagent.ps1"

Write-Host ""
Write-Host "Commit to Github."

# Commit everything to github
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\commit.ps1"

Write-Host ""
Write-Host "Program Completed."