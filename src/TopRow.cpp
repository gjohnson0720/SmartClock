#include "TopRow.h"
#include "LabelWidget.h"

TopRow::TopRow()
{
    const static char* fontName = "FreeSans";

    GdkRGBA red_color {1.0, .0, .0, 1.0};
    timeLabel = new LabelWidget("        ", &red_color, 400);
    ampmLabel = new LabelWidget("", &red_color, 36);
    dateLabel = new LabelWidget("     ", &red_color, 96);
    tempLabel = new LabelWidget("   67", &red_color, 96);
    tempUnitsLabel = new LabelWidget("°F", &red_color, 20);
    dayLabel = new LabelWidget("Mon", &red_color, 96);

    // gtk_widget_set_margin_start (ampmLabel->Widget(), 60);

    GtkWidget* rightColumn = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget* tempRow = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start ( GTK_BOX(tempRow), ampmLabel->Widget(), 0, 0, 0 );
    gtk_box_pack_start ( GTK_BOX(tempRow), tempLabel->Widget(), 0, 0, 0 );
    gtk_box_pack_start ( GTK_BOX(tempRow), tempUnitsLabel->Widget(), 0, 0, 0 );
    gtk_box_pack_start ( GTK_BOX(rightColumn), tempRow, 0, 0, 0 );
    gtk_box_pack_start ( GTK_BOX(rightColumn), dayLabel->Widget(), 0, 0, 0 );
    gtk_box_pack_start ( GTK_BOX(rightColumn), dateLabel->Widget(), 0, 0, 0 );
    gtk_widget_set_valign  (rightColumn, GTK_ALIGN_CENTER);

    row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    // gtk_box_pack_start ( GTK_BOX(row), ampmLabel->Widget(), 0, 0, 0 );
    gtk_box_pack_start ( GTK_BOX(row), timeLabel->Widget(), 0, 0, 0 );
    gtk_box_pack_start ( GTK_BOX(row), rightColumn, 0, 0, 0 );
    gtk_widget_set_valign  (timeLabel->Widget(), GTK_ALIGN_CENTER);

    timer = g_timeout_add (1000, Update, this);
}

TopRow::~TopRow()
{
    
}

gboolean TopRow::Update (gpointer data)
{
    TopRow* pThis = (TopRow*)data;
    pThis->Update();
    return G_SOURCE_CONTINUE;
}

void TopRow::Update()
{
    char time_buffer[12];
    char ampm_buffer[4];
    char date_buffer[8];
    time_t now;
    time(&now);
    struct tm *tm = localtime(&now);
    /* --- Change the label to show new time --- */
    if (tm->tm_hour >= 12)
    {
        strcpy(ampm_buffer, "PM");
    }
    else
    {
        strcpy(ampm_buffer, "AM");
    }
    if (tm->tm_hour > 12)
        tm->tm_hour -= 12;
    sprintf (time_buffer, "%2d:%02d", tm->tm_hour, tm->tm_min);//, tm->tm_sec);
    timeLabel->SetText(time_buffer);
    ampmLabel->SetText(ampm_buffer);

    sprintf (date_buffer, "%2d/%02d", tm->tm_mon + 1, tm->tm_mday);
    dateLabel->SetText(date_buffer);
}