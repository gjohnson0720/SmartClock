#pragma once

#include <gtk/gtk.h>

class LabelWidget;

class TopRow
{
public:
    TopRow();
    ~TopRow();

    GtkWidget* Widget() { return row; }

private:
    LabelWidget* timeLabel;
    LabelWidget* ampmLabel;
    LabelWidget* dateLabel;
    LabelWidget* tempLabel;
    LabelWidget* tempUnitsLabel;
    LabelWidget* dayLabel;
    GtkWidget* row;
    gint timer;

    static gboolean Update (gpointer data);
    void Update();
};