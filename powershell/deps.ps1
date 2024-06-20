# build.ps1

# Run the dependency generator
Write-Output "Running dependency generator..."
python C:/Users/desto/Scripts/projects/nodes_and_dots/python/deps.py

# Run CMake to configure and build the project
Write-Output "Running CMake..."
cmake -S . -B build
cmake --build build

Write-Output "Build complete."