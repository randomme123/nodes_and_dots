# Build exe
Write-Host ""
Write-Host "Build .exe."
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\build.ps1"

# Generate docs
Write-Host ""
Write-Host "Generate Documentation."
& "C:\Program Files\Python\Python312\python.exe" "C:\Users\desto\Scripts\projects\nodes_and_dots\python\autodoc.py"

# Run exe
Write-Host ""
Write-Host "Run .exe."
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\run.ps1"

# Clean up the build directory and documentation
Write-Host ""
Write-Host "Clean Up."
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\clean.ps1"

# Start ssh service
Write-Host ""
Write-Host "Start SSH Service."
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\sshagent.ps1"

# Commit to GitHub
Write-Host ""
Write-Host "Commit to GitHub."
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\commit.ps1"

# finish up
Write-Host ""
Write-Host "Program Completed."
