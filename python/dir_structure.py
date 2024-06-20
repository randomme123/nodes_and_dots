import os

def print_directory_structure(root_dir, indent=''):
    """
    Prints the directory structure of a given directory.

    Args:
        root_dir (str): The root directory whose structure is to be printed.
        indent (str): A string used for indentation to visually represent the directory structure. Default is an empty string.

    The function ignores any directories or files containing ".git" in their names.

    Notes:
        - This function prints the directory structure to the console.
        - Hidden files and directories (starting with a dot) are not ignored unless they contain ".git".
    """

    for item in os.listdir(root_dir):
        if ".git" in item:
            continue
        item_path = os.path.join(root_dir, item)
        if os.path.isdir(item_path):
            print(f"{indent}├── {item}/")
            print_directory_structure(item_path, indent + '│   ')
        else:
            print(f"{indent}├── {item}")

if __name__ == "__main__":
    current_directory = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    print(f"\nStart of Directory Structure:\n\n{current_directory}")
    print_directory_structure(current_directory)
    print("\nEnd of Directory Structure\n")
