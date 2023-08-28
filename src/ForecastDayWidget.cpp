#include "ForecastDayWidget.h"
#include "LabelWidget.h"
#include <sstream>

ForecastDayWidget::ForecastDayWidget()
{
    const static char* fontName = "FreeSans";
    GdkRGBA red_color {1.0, .0, .0, 1.0};
    dayLabel = new LabelWidget("TODAY", &red_color, 24);
    dayTemp = new LabelWidget("32° / 99°", &red_color, 24);
    dayWeather = new LabelWidget("Sunny", &red_color, 24);
    dayImage = gtk_image_new_from_file ("./images/1.svg");

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_vexpand (box, TRUE);
    gtk_box_pack_start ( GTK_BOX(box), dayImage, 0, 0, 5 );
    gtk_box_pack_start ( GTK_BOX(box), dayLabel->Widget(), 0, 0, 0 );
    gtk_box_pack_start ( GTK_BOX(box), dayWeather->Widget(), 0, 0, 0 );
    gtk_box_pack_start ( GTK_BOX(box), dayTemp->Widget(), 0, 0, 0 );
}
 
ForecastDayWidget::~ForecastDayWidget()
{
    
}


void ForecastDayWidget::SetData(const ForecastDayData& data_)
{
    data = data_;
    gdk_threads_add_idle(SetCb, this);
}


gboolean ForecastDayWidget::SetCb(gpointer userdata)
{
    ForecastDayWidget* widget = (ForecastDayWidget*)userdata;
    widget->SetInvoke(widget->data);
    return G_SOURCE_CONTINUE;
}

void ForecastDayWidget::SetInvoke(const ForecastDayData& data_)
{
    dayLabel->SetText(data.Day);
    std::string temp = std::to_string(data.MinTemp) + "° / " + std::to_string(data.MaxTemp) + "°";
    dayTemp->SetText(temp);
    dayWeather->SetText(data.Description);
    std::stringstream s;
    s << "./images/" << data.Icon << ".svg";
    gtk_image_set_from_file((GtkImage*)dayImage, s.str().c_str());
}