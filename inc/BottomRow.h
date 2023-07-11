#pragma once

#include <array>
#include <vector>
#include <gtk/gtk.h>
#include "ForecastDayData.h"

class ForecastDayWidget;

class BottomRow
{
public:
    BottomRow();
    ~BottomRow();

    GtkWidget* Widget() { return row; }

    void Update(const std::vector<ForecastDayData>& data);

private:
    std::array<ForecastDayWidget*, 5> forecastDays;
    GtkWidget* row;
    // gint timer;

    // static gboolean Update (gpointer data);
    // void Update();
};