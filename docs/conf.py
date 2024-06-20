import os
import sys

# Add the path to the Python source directory
sys.path.insert(0, os.path.abspath('../python'))

# -- Project information -----------------------------------------------------
project = 'dots_and_nodes'
copyright = '2024, xonnel'
author = 'xonnel'
release = '0.01'

# -- General configuration ---------------------------------------------------
extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.autosummary',
    'breathe',
    # Add any other Sphinx extensions here
]

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

# -- Options for HTML output -------------------------------------------------
html_theme = 'alabaster'
html_static_path = ['_static']

# Autodoc settings
autodoc_default_options = {
    'members': True,
    'undoc-members': True,
    'private-members': True,
    'special-members': True,
    'inherited-members': True,
    'show-inheritance': True,
}

# Autosummary settings
autosummary_generate = True  # Automatically generate stub files

# Breathe configuration
breathe_projects = {
    "dots_and_nodes": "doxygen/xml"
}
breathe_default_project = "dots_and_nodes"
