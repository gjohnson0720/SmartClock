#include <gtk/gtk.h>
#include "ForecastDayData.h"

class LabelWidget;

class ForecastDayWidget
{
public:
    ForecastDayWidget();
    ~ForecastDayWidget();

    GtkWidget* Widget() { return box; }
    void SetData(const ForecastDayData& data);

private:
    LabelWidget* dayLabel;
    LabelWidget* dayTemp;
    LabelWidget* dayWeather;
    GtkWidget* box;
    GtkWidget* dayImage;

    ForecastDayData data;

    static gboolean SetCb(gpointer userdata);
    void SetInvoke(const ForecastDayData& data_);
};
