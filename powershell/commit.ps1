# Define variables
$projectDir = "C:\Users\desto\Scripts\projects\nodes_and_dots"
$timestamp = Get-Date -Format "yyyy-MM-dd HH:mm:ss"
$commitMessage = "Automated commit after build and run - $timestamp"

# Navigate to the project directory
Set-Location $projectDir

# Add all changes to the staging area
git add .

# Commit the changes with a message
git commit -m $commitMessage

# Push the changes to the remote repository
git push origin main

Write-Host "Code committed and pushed to GitHub."