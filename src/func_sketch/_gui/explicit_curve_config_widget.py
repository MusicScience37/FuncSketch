"""Class of widgets to configure curves defined by explicit functions."""

import kivy.properties
import kivy.uix.boxlayout


class ExplicitCurveConfigWidget(kivy.uix.boxlayout.BoxLayout):
    """Class of widgets to configure curves defined by explicit functions."""

    curve_name = kivy.properties.StringProperty("Function")
    error_message = kivy.properties.StringProperty("")
    expression_text = kivy.properties.StringProperty("")
