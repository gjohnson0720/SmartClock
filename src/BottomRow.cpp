#include "BottomRow.h"
#include "LabelWidget.h"
#include "ForecastDayWidget.h"
#include "log.h"

BottomRow::BottomRow()
{
    for (int i = 0; i < forecastDays.size(); ++i)
    {
        forecastDays[i] = new ForecastDayWidget();
    }

    row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    for (int i = 0; i < forecastDays.size(); ++i)
    {
        gtk_box_pack_start ( GTK_BOX(row), forecastDays[i]->Widget(), 0, 0, 0 );
        gtk_widget_set_margin_start (forecastDays[i]->Widget(), 60);
    }
    gtk_widget_set_halign  (row, GTK_ALIGN_CENTER);
}

BottomRow::~BottomRow()
{
}

void BottomRow::Update(const std::vector<ForecastDayData>& data)
{
    FILE_LOG(linfo) << " BottomRow Update start" << std::endl;
    auto numDays = std::min(forecastDays.size(), data.size());
    for(int i = 0; i < numDays; i++)
    {
        forecastDays[i]->SetData(data[i]);
    }
    FILE_LOG(linfo) << " BottomRow Update done" << std::endl;
}