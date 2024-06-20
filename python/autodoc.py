import os
import subprocess

def build_docs():
    """
    Builds the HTML documentation for the project using Sphinx and Doxygen.

    This function performs the following steps:
    1. Defines the paths for the documentation source directory (`docs`) and the build output directory (`_build/html`).
    2. Ensures the configuration file (`conf.py`) exists in the `docs` directory.
    3. Runs Doxygen to generate the XML documentation.
    4. Runs the `sphinx-build` command to generate the HTML documentation.
    5. Prints a success message with the location of the generated documentation or an error message if the build fails.

    Raises:
        FileNotFoundError: If the `conf.py` file is not found in the `docs` directory.
        subprocess.CalledProcessError: If the `doxygen` or `sphinx-build` command fails.

    Example:
        To build the documentation, simply run the script:
        
        > python autodoc.py
    """
    # Define the path to the docs directory and the build directory
    docs_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '../docs'))
    build_dir = os.path.join(docs_dir, '_build', 'html')

    # Ensure the docs directory contains the conf.py file
    conf_path = os.path.join(docs_dir, 'conf.py')
    if not os.path.exists(conf_path):
        raise FileNotFoundError(f"Configuration file not found at: {conf_path}")

    # Run Doxygen to generate XML documentation
    try:
        subprocess.run(['doxygen', 'Doxyfile'], check=True)
        print("Doxygen documentation generated successfully.")
    except subprocess.CalledProcessError as e:
        print(f"Failed to generate Doxygen documentation: {e}")
        return

    # Run the sphinx-build command
    try:
        subprocess.run(['sphinx-build', '-b', 'html', docs_dir, build_dir], check=True)
        print(f"Documentation built successfully. See {build_dir} for the output.")
    except subprocess.CalledProcessError as e:
        print(f"Failed to build documentation: {e}")

if __name__ == "__main__":
    build_docs()
