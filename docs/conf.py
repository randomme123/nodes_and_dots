import os
import sys
import breathe
import sphinx_rtd_theme

# Add project root and docs root to sys.path
sys.path.insert(0, os.path.abspath('..'))
sys.path.insert(0, os.path.abspath('.'))

# Project information
project = 'dots_and_nodes'
author = 'Xonnel'
release = '0.1'

# Sphinx extensions
extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.napoleon',
    'breathe',
]

# Breathe configuration
breathe_projects = {
    "dots_and_nodes": "./doxygen/xml"
}
breathe_default_project = "dots_and_nodes"

# Paths
templates_path = ['_templates']
exclude_patterns = []

# HTML output
html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']
