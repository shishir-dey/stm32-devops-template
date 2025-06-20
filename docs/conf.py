# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'STM32 DevOps Template'
copyright = '2025, Shishir Dey'
author = 'Shishir Dey'
release = 'v1.0.0'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.viewcode',
    'sphinx.ext.napoleon',
    'sphinx.ext.githubpages',
    'breathe',
    'myst_parser',
]

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']

# -- Breathe configuration ---------------------------------------------------
breathe_projects = {
    "STM32DevOpsTemplate": "./doxygen/xml"
}
breathe_default_project = "STM32DevOpsTemplate"

# -- MyST configuration ------------------------------------------------------
myst_enable_extensions = [
    "amsmath",
    "colon_fence",
    "deflist",
    "dollarmath",
    "html_admonition",
    "html_image",
    "linkify",
    "replacements",
    "smartquotes",
    "substitution",
    "tasklist",
]

# -- Additional configuration ------------------------------------------------
html_title = f"{project} {release}"
html_short_title = project
html_show_sourcelink = False
html_show_sphinx = False
html_show_copyright = True

# Add GitHub link
html_context = {
    'display_github': True,
    'github_user': 'shishir-dey',
    'github_repo': 'stm32-devops-template',
    'github_version': 'main/',
    'conf_py_path': '/docs/',
} 