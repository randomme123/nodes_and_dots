# Run the build script
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\build.ps1"

# Run the application
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\run.ps1"

# Clean up the build directory
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\clean.ps1"

# start ssh service
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\sshagent.ps1"

# Commit everything to github
& "C:\Users\desto\Scripts\projects\nodes_and_dots\powershell\commit.ps1"

Write-Host "All tasks completed."