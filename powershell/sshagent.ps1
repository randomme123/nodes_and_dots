# Path to your SSH key
$sshKeyPath = "C:\Users\desto\Documents\keys\github\github_ssh_key"

# Check if the SSH agent service is running
$service = Get-Service -Name ssh-agent
if ($service.Status -eq 'Running') {
    Write-Host "SSH agent is running."
} else {
    Write-Host "SSH agent is not running. Starting it now..."
    Start-Service -Name ssh-agent
    Write-Host "SSH agent started."
}

# Check if the SSH key is added to the agent
$keys = ssh-add -l
if ($keys) {
    Write-Host "SSH agent is loaded with keys:"
    $keys
} else {
    Write-Host "No SSH keys added to the agent. Adding key now..."
    ssh-add $sshKeyPath

    # Verify if the key was added
    $keys = ssh-add -l
    if ($keys) {
        Write-Host "SSH key added successfully."
        $keys
    } else {
        Write-Host "Failed to add SSH key. Please check the key path and passphrase."
    }
}
