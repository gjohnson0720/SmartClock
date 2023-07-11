#pragma once

#include <gtk/gtk.h>
#include <string>

class LabelWidget
{
public:  
    LabelWidget(std::string initialString = "", GdkRGBA* color = nullptr, int fontSize = -1);
    ~LabelWidget();

    GtkWidget* Widget() { return label; }

    void SetText(std::string text);

private:
    GtkWidget* label;
};