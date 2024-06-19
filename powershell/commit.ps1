# Define variables
$projectDir = "C:\Users\desto\Scripts\projects\nodes_and_dots"
$timestamp = Get-Date -Format "yyyy-MM-dd HH:mm:ss"
$commitMessage = "Automated commit after build and run - $timestamp"

# Navigate to the project directory
Set-Location $projectDir

# Add all changes to the staging area
git add -A

# Commit the changes with a message if there are any changes
if ((git diff --cached --exit-code) -ne 0) {
    git commit -m $commitMessage
    git push origin main
    Write-Host "Code committed and pushed to GitHub."
} else {
    Write-Host "No changes to commit."
}