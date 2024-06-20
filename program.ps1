Write-Host ""
Write-Host "Build .exe."

& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\build.ps1"

Write-Host ""
Write-Host "Run .exe."

# Run the application
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\run.ps1"

Write-Host ""
Write-Host "Generate Documentation."

# Generate the documentation
& "C:\Program Files\Python\Python312\python.exe" "C:\Users\desto\Scripts\projects\nodes_and_dots\python\autodoc.py"

Write-Host ""
Write-Host "Clean Up Documentation."

# Clean up the docs directory
Remove-Item -Recurse -Force "C:\Users\desto\Scripts\projects\nodes_and_dots\docs\_build\doctrees"
Remove-Item -Recurse -Force "C:\Users\desto\Scripts\projects\nodes_and_dots\docs\_build\*.log"
Remove-Item -Recurse -Force "C:\Users\desto\Scripts\projects\nodes_and_dots\docs\_autosummary"

Write-Host ""
Write-Host "Clean Up Build Directory."

# Clean up the build directory
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\clean.ps1"

Write-Host ""
Write-Host "Start SSH Service."

# Start ssh service
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\sshagent.ps1"

Write-Host ""
Write-Host "Commit to GitHub."

# Commit everything to GitHub
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\commit.ps1"

Write-Host ""
Write-Host "Program Completed."
