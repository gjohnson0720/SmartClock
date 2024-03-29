#include "ForecastDayWidget.h"
#include "LabelWidget.h"
#include <sstream>

ForecastDayWidget::ForecastDayWidget()
{
    const static char* fontName = "FreeSans";
    GdkRGBA red_color {1.0, .0, .0, 1.0};
    dayLabel = new LabelWidget("", &red_color, 24);
    dayTemp = new LabelWidget("", &red_color, 24);
    dayWeather = new LabelWidget("", &red_color, 24);
    dayImage = gtk_image_new_from_file ("does_not_exist.svg");

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
    if (data != data_)
    {
        data = data_;
        dayLabel->SetText(data.Day);
        std::string temp = std::to_string(data.MinTemp) + "° / " + std::to_string(data.MaxTemp) + "°";
        dayTemp->SetText(temp);
        dayWeather->SetText(data.Description);
        std::stringstream s;
        s << "./images/" << data.Icon << ".svg";
        gtk_image_clear((GtkImage*)dayImage);
        gtk_image_set_from_file((GtkImage*)dayImage, s.str().c_str());
    }
}

