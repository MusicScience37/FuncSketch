"""Class of FuncSketch GUI application."""

import pathlib

import kivy.app
import kivy.lang

from func_sketch._gui.func_sketch_widget import FuncSketchWidget

THIS_DIR = pathlib.Path(__file__).absolute().parent


class FuncSketchApp(kivy.app.App):
    """Class of FuncSketch GUI application."""

    def build(self):
        """Build the GUI application."""
        kivy.lang.Builder.load_file(str(THIS_DIR / "func_sketch_widget.kv"))
        return FuncSketchWidget()


if __name__ == "__main__":
    FuncSketchApp().run()
