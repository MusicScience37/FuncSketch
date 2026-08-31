"""Sphinx configuration."""

# pylint: disable=invalid-name
# pylint: disable=redefined-builtin

import collections.abc
import pathlib
import re
import typing

import docutils.nodes
import sphinx.addnodes
import sphinx.application
import sphinx.builders
import sphinx.directives
import sphinx.domains
import sphinx.environment
import sphinx.roles
import sphinx.util.docfields
import sphinx.util.nodes

THIS_DIR = pathlib.Path(__file__).absolute().parent

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

todo_include_todos = True

# -- Options for PlantUML ----------------------------------------------------

extensions += ["sphinxcontrib.plantuml"]

plantuml_output_format = "svg"
plantuml_syntax_error_image = True

# -- Options for Myst-Parser and Myst-NB -------------------------------------

# Myst-NB automatically enables Myst-Parser.
extensions += ["myst_nb"]

myst_enable_extensions = [
    "tasklist",
    "dollarmath",
]

myst_heading_anchors = 4

nb_execution_mode = "cache"
nb_execution_cache_path = str(THIS_DIR.parent.parent / ".jupyter_cache")

# setting of MathJax
# Extension for MathJax is already enabled by myst_nb.
# MathJax URL working with Plotly was written in https://www.npmjs.com/package/plotly.js/v/3.0.1.
mathjax_path = "https://cdn.jsdelivr.net/npm/mathjax@3.2.2/es5/tex-svg.js"
mathjax3_config = {
    "tex": {
        "inlineMath": [["$", "$"], ["\\(", "\\)"]],
        "displayMath": [["$$", "$$"], ["\\[", "\\]"]],
        "macros": {
            "bm": ["{\\boldsymbol{#1}}", 1],
        },
    },
}
mathjax_options = {
    "defer": None,
}

# -- Options for HTML output -------------------------------------------------

html_theme = "sphinx_orange_book_theme"
html_static_path: list[str] = []
html_favicon = "../icon/icon.svg"
html_theme_options = {
    "logo": {
        "image_light": "../icon/icon_web_light.svg",
        "image_dark": "../icon/icon_web_dark.svg",
        "text": "FuncSketch",
    },
    # pygments configuration must be specified here.
    "pygments_light_style": "gruvbox-light",
    "pygments_dark_style": "native",
    "repository_url": "https://gitlab.com/MusicScience37Projects/experiments/func-sketch",
    "use_repository_button": True,
}


# -- Definition of funcsketch domain -----------------------------------------

# cspell: ignore signode, fromdocname, contnode, docname, todocname, refnode
# cspell: ignore paramlist, parameterlist, docfields, returnvalue, returntype
# cspell: ignore typenames
# pylint: disable=abstract-method, too-many-arguments, too-many-positional-arguments


class FuncSketchFunctionDescription(sphinx.directives.ObjectDescription):
    """Directive for function description in FuncSketch."""

    # Doc fields available in the content of ``funcsketch:function`` directives.
    #
    # These are rendered in the order listed here, regardless of the order in
    # which they are written in the .rst source, so that all function
    # descriptions end up with a consistent structure:
    #
    # - Parameters: Name, type, and description of each parameter.
    # - Definition: Formula defining the function (e.g. :math:`e^x`).
    # - Domain: Set of input values for which the function is defined.
    # - Range: Set of values the function can return.
    # - Returns: Description of the return value in prose.
    # - Return type: Type of the return value.
    #
    # ``Definition``, ``Domain``, and ``Range`` are especially important for
    # special functions (e.g. Bessel functions), which often have multiple
    # conventions, restrictions on parameters (e.g. integer vs. real order),
    # and non-trivial domains or ranges.
    doc_field_types = [
        sphinx.util.docfields.TypedField(
            "parameter",
            label="Parameters",
            names=("param", "parameter"),
            typenames=("type",),
            can_collapse=True,
        ),
        sphinx.util.docfields.Field(
            "definition",
            label="Definition",
            has_arg=False,
            names=("definition",),
        ),
        sphinx.util.docfields.Field(
            "domain",
            label="Domain",
            has_arg=False,
            names=("domain",),
        ),
        sphinx.util.docfields.Field(
            "range",
            label="Range",
            has_arg=False,
            names=("range",),
        ),
        sphinx.util.docfields.Field(
            "returnvalue",
            label="Returns",
            has_arg=False,
            names=("returns", "return"),
        ),
        sphinx.util.docfields.Field(
            "returntype",
            label="Return type",
            has_arg=False,
            names=("rtype",),
        ),
    ]

    def handle_signature(
        self, sig: str, signode: sphinx.addnodes.desc_signature
    ) -> str:
        """Handle signature of function description.

        The signature may include arguments, e.g. ``sin(x)``, but only the
        function name (``sin``) is used as the name for cross-references, so
        that roles can refer to it without arguments.

        Returns:
            str: Name of the function.
        """
        match = re.match(r"^\s*(\w+)\s*\((.*)\)\s*$", sig)
        if match is None:
            name = sig.strip()
            args = None
        else:
            name = match.group(1)
            args = match.group(2)

        signode += sphinx.addnodes.desc_name(name, name)
        if args is not None:
            paramlist = sphinx.addnodes.desc_parameterlist()
            for arg in args.split(","):
                arg = arg.strip()
                if arg:
                    paramlist += sphinx.addnodes.desc_parameter(arg, arg)
            signode += paramlist

        # Remember the plain name so that ``_toc_entry_name`` below can build
        # a table-of-contents entry for this function.
        signode["funcsketch_name"] = name

        return name

    def get_signature_prefix(self, _sig: str) -> str:
        """Get signature prefix of function description.

        Returns:
            str: Signature prefix, always ``"function"``.
        """
        return "function"

    def _object_hierarchy_parts(
        self, sig_node: sphinx.addnodes.desc_signature
    ) -> tuple[str, ...]:
        """Get the hierarchy of names of the object for table-of-contents entries.

        Functions in FuncSketch have no hierarchy (no submodules, classes,
        etc.), so this is simply a single-element tuple with the function
        name.

        Returns:
            tuple[str, ...]: Hierarchy of names, empty if the signature node
            has no name.
        """
        name = sig_node.get("funcsketch_name")
        if name is None:
            return ()
        return (name,)

    def _toc_entry_name(self, sig_node: sphinx.addnodes.desc_signature) -> str:
        """Get the text of the table-of-contents entry for this function.

        Overriding this (together with ``_object_hierarchy_parts``) is what
        makes ``funcsketch:function`` entries show up in ``.. toctree::``
        listings and the theme's sidebar navigation, the same mechanism the
        built-in Python domain uses for ``py:function`` etc.
        See :py:meth:`sphinx.directives.ObjectDescription._toc_entry_name`.

        Note that this method and ``_object_hierarchy_parts`` are prefixed
        with an underscore in Sphinx itself, meaning they are not part of
        Sphinx's officially stable extension API (unlike ``handle_signature``
        etc.). Their behavior should be re-checked when upgrading to a new
        major version of Sphinx.

        Returns:
            str: Table-of-contents entry text, empty if the signature node
            has no hierarchy parts.
        """
        if not sig_node.get("_toc_parts"):
            return ""
        (name,) = sig_node["_toc_parts"]
        return f"{name}()"

    def add_target_and_index(
        self, name: str, _sig: str, signode: sphinx.addnodes.desc_signature
    ) -> None:
        """Add a target for cross-references and register in the domain."""
        node_id = sphinx.util.nodes.make_id(
            self.env, self.state.document, "funcsketch-function", name
        )
        signode["ids"].append(node_id)
        self.state.document.note_explicit_target(signode)
        domain = typing.cast(FuncSketchDomain, self.env.get_domain("funcsketch"))
        domain.note_function(name, node_id)


class FuncSketchDomain(sphinx.domains.Domain):
    """Domain for FuncSketch."""

    name = "funcsketch"
    label = "FuncSketch"
    object_types = {"function": sphinx.domains.ObjType("function", "func")}
    directives = {"function": FuncSketchFunctionDescription}
    roles = {"func": sphinx.roles.XRefRole()}
    initial_data = {"functions": {}}

    @property
    def functions(self) -> dict[str, tuple[str, str]]:
        """Dictionary of function names to (docname, node ID)."""
        return self.data.setdefault("functions", {})

    def note_function(self, name: str, node_id: str) -> None:
        """Register a function described in the current document."""
        self.functions[name] = (self.env.docname, node_id)

    def clear_doc(self, docname: str) -> None:
        """Remove functions described in the given document."""
        for name, (fn_docname, _) in list(self.functions.items()):
            if fn_docname == docname:
                del self.functions[name]

    def get_objects(
        self,
    ) -> collections.abc.Iterable[tuple[str, str, str, str, str, int]]:
        """Get descriptions of all functions in this domain.

        Yields:
            tuple[str, str, str, str, str, int]: Name, display name, object
            type, docname, node ID, and priority of each function.
        """
        for name, (docname, node_id) in self.functions.items():
            yield name, name, "function", docname, node_id, 1

    def resolve_xref(
        self,
        env: sphinx.environment.BuildEnvironment,
        fromdocname: str,
        builder: sphinx.builders.Builder,
        typ: str,
        target: str,
        node: sphinx.addnodes.pending_xref,
        contnode: sphinx.addnodes.Element,
    ) -> docutils.nodes.reference | None:
        """Resolve cross-reference.

        Returns:
            docutils.nodes.reference | None: Reference node, or ``None`` if
            the target function is not found.
        """
        entry = self.functions.get(target)
        if entry is None:
            return None
        todocname, node_id = entry
        return sphinx.util.nodes.make_refnode(
            builder, fromdocname, todocname, node_id, contnode, target
        )


def setup(app: sphinx.application.Sphinx) -> dict[str, bool]:
    """Set up this Sphinx extension.

    Returns:
        dict[str, bool]: Metadata for this Sphinx extension.
    """
    app.add_domain(FuncSketchDomain)
    return {"parallel_read_safe": False, "parallel_write_safe": True}
