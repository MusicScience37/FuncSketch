"""Sphinx configuration."""

# pylint: disable=invalid-name
# pylint: disable=redefined-builtin

# -- Project information -----------------------------------------------------

project = "FuncSketch"
copyright = "2026, Kenta Kabashima"
author = "Kenta Kabashima"

# -- General configuration ---------------------------------------------------

extensions = [
    "sphinx.ext.todo",
    "sphinx.ext.autodoc",
    "sphinx.ext.napoleon",
]

templates_path: list[str] = []
exclude_patterns: list[str] = []

autodoc_default_options = {
    "no-value": True,
}

# -- Options for PlantUML ----------------------------------------------------

extensions += ["sphinxcontrib.plantuml"]

plantuml_output_format = "svg"
plantuml_syntax_error_image = True

# -- Options for Myst-Parser -------------------------------------------------

extensions += ["myst_parser"]

myst_enable_extensions = [
    "tasklist",
]

myst_heading_anchors = 4

# -- Options for HTML output -------------------------------------------------

html_theme = "sphinx_orange_book_theme"
html_static_path: list[str] = []

html_theme_options = {
    # pygments configuration must be specified here.
    "pygments_light_style": "gruvbox-light",
    "pygments_dark_style": "native",
    "repository_url": "https://gitlab.com/MusicScience37Projects/experiments/func-sketch",
    "use_repository_button": True,
}
