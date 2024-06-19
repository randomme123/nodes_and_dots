import sys
import subprocess
import os

# Check if the correct number of arguments is passed
if len(sys.argv) != 3:
    print("Usage: python add_ssh_key.py <key_path> <passphrase>")
    sys.exit(1)

# Path to the SSH key and passphrase
key_path = sys.argv[1]
passphrase = sys.argv[2]

# Create a temporary batch file to run ssh-add with the passphrase
batch_script = f"""
@echo off
echo {passphrase} | ssh-add {key_path}
"""

# Write the batch script to a temporary file
batch_file_path = "add_ssh_key.bat"
with open(batch_file_path, "w") as batch_file:
    batch_file.write(batch_script)

try:
    # Run the batch file
    result = subprocess.run([batch_file_path], capture_output=True, text=True)

    if result.returncode == 0:
        print("SSH key added successfully.")
    else:
        print(f"An error occurred: {result.stderr.strip()}")
finally:
    # Remove the temporary batch file
    os.remove(batch_file_path)
