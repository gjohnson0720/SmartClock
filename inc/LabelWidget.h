#pragma once

#include <gtk/gtk.h>
#include <string>

class LabelWidget
{
public:  
    LabelWidget(const std::string& initialString = "", GdkRGBA* color = nullptr, int fontSize = -1);
    ~LabelWidget();

    GtkWidget* Widget() { return label; }

    void SetText(const std::string& text);

private:
    GtkWidget* label;
};
