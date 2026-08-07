"""Class of widgets to configure curves."""

import kivy.properties
import kivy.uix.boxlayout


class CurveConfigWidget(kivy.uix.boxlayout.BoxLayout):
    """Class of widgets to configure curves."""

    curve_name = kivy.properties.StringProperty("Function")
    error_message = kivy.properties.StringProperty("")
    expression_text = kivy.properties.StringProperty("")
