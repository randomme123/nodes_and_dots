# Path to your SSH key
$sshKeyPath = "C:\Users\desto\Documents\keys\github\github_ssh_key"

# Check if the SSH agent service is running
$service = Get-Service -Name ssh-agent
if ($service.Status -eq 'Running') {
    Write-Host "SSH agent is running." -ForegroundColor Cyan
} else {
    Write-Host "SSH agent is not running. Starting it now..." -ForegroundColor Cyan
    Start-Service -Name ssh-agent
    Write-Host "SSH agent started." -ForegroundColor Cyan
}

# Check if the SSH key is added to the agent
$keys = ssh-add -l
if ($keys) {
    Write-Host "SSH agent is loaded with keys:" -ForegroundColor Cyan
    $keys
} else {
    Write-Host "No SSH keys added to the agent. Adding key now..." -ForegroundColor Cyan
    ssh-add $sshKeyPath

    # Verify if the key was added
    $keys = ssh-add -l
    if ($keys) {
        Write-Host "SSH key added successfully." -ForegroundColor Cyan
        $keys
    } else {
        Write-Host "Failed to add SSH key. Please check the key path and passphrase." -ForegroundColor Red
    }
}


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
    Write-Host "Code committed and pushed to GitHub." -ForegroundColor Cyan
} else {
    Write-Host "No changes to commit." -ForegroundColor Cyan
}