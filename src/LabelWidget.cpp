#include "LabelWidget.h"
#include <iostream>

const static char* fontName = "FreeSans";

LabelWidget::LabelWidget(const std::string& initialString, GdkRGBA* color_, int fontSize_) 
{
    label = gtk_label_new(initialString.c_str());
    if (color_ != nullptr)
    {
        gtk_widget_override_color(label, GtkStateFlags::GTK_STATE_FLAG_NORMAL, color_);
    }
    if (fontSize_ > 0)
    {
        font_description = pango_font_description_new();
        pango_font_description_set_family(font_description, fontName);
        pango_font_description_set_size(font_description, fontSize_ * PANGO_SCALE);
        pango_font_description_set_weight(font_description, PangoWeight::PANGO_WEIGHT_BOLD);
        gtk_widget_override_font(label, font_description);
    }
}

LabelWidget::~LabelWidget()
{
    if(font_description != nullptr)
    {
        pango_font_description_free(font_description);
        font_description = nullptr;
    }
}

void LabelWidget::SetText(const std::string& text_)
{
    text = text_;
    gtk_label_set_text (GTK_LABEL (label), text.c_str());
}