# Define variables
$buildDir = "C:\Users\desto\Scripts\projects\nodes_and_dots\game\build"
$exeFile = "$buildDir\Debug\nodes_and_dots.exe"
$projectDir = "C:\Users\desto\Scripts\projects\nodes_and_dots\game"

# Execute the built application
if (Test-Path $exeFile) {
    Write-Host "Executing the application..."
    $process = Start-Process -FilePath $exeFile -NoNewWindow -PassThru
    # Wait for the process to exit
    $process.WaitForExit()
    Write-Host "Application exited."
    # Navigate back to the project directory
    Set-Location $projectDir
} else {
    Write-Host "Error: Executable file not found at $exeFile"
}
