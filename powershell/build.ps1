# Define variables
$projectDir = "C:\Users\desto\Scripts\projects\nodes_and_dots\game"
$buildDir = "$projectDir\build"
$vcpkgToolchainFile = "C:/Tools/vcpkg/scripts/buildsystems/vcpkg.cmake"
$sfmlBinDir = "C:\Tools\vcpkg\installed\x64-windows\bin"
$dllFiles = @("sfml-graphics-2.dll", "sfml-window-2.dll", "sfml-system-2.dll")

Set-Location $projectDir

# Create build directory if it does not exist
if (-Not (Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir
}

# Navigate to the build directory
Set-Location $buildDir

# Run CMake to configure the project
cmake -DCMAKE_TOOLCHAIN_FILE="$vcpkgToolchainFile" ..

# Build the project
cmake --build .

# Copy SFML DLLs to the build directory
foreach ($dll in $dllFiles) {
    $sourceDll = "$sfmlBinDir\$dll"
    $destinationDll = "$buildDir\Debug\$dll"
    if (Test-Path $sourceDll) {
        Copy-Item -Path $sourceDll -Destination $destinationDll -Force
    } else {
        Write-Host "Warning: $sourceDll not found."
    }
}

Write-Host "Build completed. DLLs copied to build directory."
