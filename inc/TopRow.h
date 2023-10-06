#pragma once

#include <gtk/gtk.h>
#include <memory>
#include <list>

class LabelWidget;

class TopRow
{
public:
    TopRow();
    ~TopRow();

    GtkWidget* Widget() { return row; }

    void UpdateGarageTemp(float value);

private:
    std::unique_ptr<LabelWidget> timeLabel;
    std::unique_ptr<LabelWidget> ampmLabel;
    std::unique_ptr<LabelWidget> dateLabel;
    std::unique_ptr<LabelWidget> tempLabel;
    std::unique_ptr<LabelWidget> tempUnitsLabel;
    std::unique_ptr<LabelWidget> dayLabel;
    std::unique_ptr<LabelWidget> activityLabel;
    GtkWidget* row;
    gint timer;
    bool activity;
    std::string current_time;

    static gboolean Update (gpointer data);
    void Update();
};