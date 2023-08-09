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
        PangoFontDescription *font_description = pango_font_description_new();
        pango_font_description_set_family(font_description, fontName);
        pango_font_description_set_size(font_description, fontSize_ * PANGO_SCALE);
        pango_font_description_set_weight(font_description, PangoWeight::PANGO_WEIGHT_BOLD);
        gtk_widget_override_font(label, font_description);
    }
}

LabelWidget::~LabelWidget()
{
    
}

struct SetInfo
{
    LabelWidget* label;
    std::string text;
    SetInfo(LabelWidget* label_, std::string text_) : label(label_), text(text_) 
    {
        std::cout << text << std::endl;
    }
};

void LabelWidget::SetText(const std::string& text_)
{
    SetInfo* info = new SetInfo(this, text_);
    gdk_threads_add_idle(SetCb, info);
    // g_main_context_invoke(NULL, SetCb, info);
}

gboolean LabelWidget::SetCb(gpointer userdata)
{
    SetInfo* info = (SetInfo*)userdata;
    info->label->SetInvoke(info->text);
    // delete info;
    return G_SOURCE_CONTINUE;
}

void LabelWidget::SetInvoke(const std::string& text_)
{
    gtk_label_set_text (GTK_LABEL (label), text_.c_str());
}