# Define variables
$buildDir = "C:\Users\desto\Scripts\projects\nodes_and_dots\cpp\build"

# Function to check if a directory is in use
function Test-DirectoryInUse {
    param (
        [string]$path
    )
    try {
        $tempFile = [System.IO.Path]::Combine($path, [System.IO.Path]::GetRandomFileName())
        $fs = [System.IO.File]::Create($tempFile)
        $fs.Close()
        Remove-Item -Path $tempFile -Force
        return $false
    } catch {
        return $true
    }
}

# Wait for the directory to be released
$maxAttempts = 10
$attempt = 0
while (Test-DirectoryInUse -path $buildDir -and $attempt -lt $maxAttempts) {
    Write-Host "Directory is in use. Waiting..."
    Start-Sleep -Seconds 1
    $attempt++
}

# Delete the build directory
if (-not (Test-DirectoryInUse -path $buildDir)) {
    if (Test-Path $buildDir) {
        Remove-Item -Recurse -Force $buildDir
        Write-Host "Build directory deleted."
    } else {
        Write-Host "Build directory not found."
    }
} else {
    Write-Host "Build directory is still in use after multiple attempts."
}












Write-Host ""
Write-Host "Clean Up Documentation."

# Clean up the docs directory
if (Test-Path "C:\Users\desto\Scripts\projects\nodes_and_dots\docs\_build\doctrees") {
    Remove-Item -Recurse -Force "C:\Users\desto\Scripts\projects\nodes_and_dots\docs\_build\doctrees"
}
Remove-Item -Recurse -Force "C:\Users\desto\Scripts\projects\nodes_and_dots\docs\_build\*.log"
if (Test-Path "C:\Users\desto\Scripts\projects\nodes_and_dots\docs\_autosummary") {
    Remove-Item -Recurse -Force "C:\Users\desto\Scripts\projects\nodes_and_dots\docs\_autosummary"
}