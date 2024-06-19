import os

def print_directory_structure(root_dir, indent=''):
    for item in os.listdir(root_dir):
        item_path = os.path.join(root_dir, item)
        if os.path.isdir(item_path):
            print(f"{indent}├── {item}/")
            print_directory_structure(item_path, indent + '│   ')
        else:
            print(f"{indent}├── {item}")

if __name__ == "__main__":
    current_directory = os.path.dirname(os.path.abspath(__file__))
    print(f"Dir-structure >>> {current_directory}:")
    print_directory_structure(current_directory)