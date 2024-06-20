import os
import subprocess

def build_docs():
    # Define the path to the docs directory and the build directory
    docs_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '../docs'))
    build_dir = os.path.join(docs_dir, '_build', 'html')

    # Ensure the docs directory contains the conf.py file
    conf_path = os.path.join(docs_dir, 'conf.py')
    if not os.path.exists(conf_path):
        raise FileNotFoundError(f"Configuration file not found at: {conf_path}")

    # Run the sphinx-build command
    try:
        subprocess.run(['sphinx-build', '-b', 'html', docs_dir, build_dir], check=True)
        print(f"Documentation built successfully. See {build_dir} for the output.")
    except subprocess.CalledProcessError as e:
        print(f"Failed to build documentation: {e}")

if __name__ == "__main__":
    build_docs()