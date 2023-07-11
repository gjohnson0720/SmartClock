#include "BottomRow.h"
#include "LabelWidget.h"
#include "ForecastDayWidget.h"

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
    // timer = g_timeout_add (60 * 60 * 1000, Update, this);
}

BottomRow::~BottomRow()
{
    
}

// gboolean BottomRow::Update (gpointer data)
// {
//     BottomRow* pThis = (BottomRow*)data;
//     pThis->Update();
//     return G_SOURCE_CONTINUE;
// }

// void BottomRow::Update()
// {

// }

void BottomRow::Update(const std::vector<ForecastDayData>& data)
{
    auto numDays = std::min(forecastDays.size(), data.size());
    for(int i = 0; i < numDays; i++)
    {
        forecastDays[i]->SetData(data[i]);
    }
}