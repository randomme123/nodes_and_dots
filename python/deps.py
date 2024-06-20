import os
import re

def find_includes(directory):
    include_pattern = re.compile(r'#include\s+[<"]([^>"]+)[">]')
    dependencies = {}

    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith('.cpp') or file.endswith('.hpp'):
                file_path = os.path.join(root, file)
                with open(file_path, 'r') as f:
                    content = f.read()
                    includes = include_pattern.findall(content)
                    dependencies[file_path] = includes

    return dependencies

def write_dependencies(dependencies, output_file):
    with open(output_file, 'w') as f:
        for source, includes in dependencies.items():
            f.write(f'{source}: {" ".join(includes)}\n')

if __name__ == "__main__":
    src_directory = 'C:\\Users\\desto\\Scripts\\projects\\nodes_and_dots\\cpp\\src'
    output_file = 'deps.d'
    deps = find_includes(src_directory)
    write_dependencies(deps, output_file)
    print(f'Dependencies written to {output_file}')
