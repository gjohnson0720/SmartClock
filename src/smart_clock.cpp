#include <gtk/gtk.h>

static gint timer = 0;
static GtkWidget* timeLabel;
static GtkWidget* ampmLabel;
static GtkWidget* dateLabel;
static GtkWidget* tempLabel;
static GtkWidget* tempUnitsLabel;
static GtkWidget* dayLabel;
static GtkWidget* grid;

gint UpdateTime (gpointer data)
{
    char time_buffer[12];
    char ampm_buffer[4];
    char date_buffer[8];
    time_t now;
    time(&now);
    struct tm *tm = localtime(&now);
    /* --- Change the label to show new time --- */
    if (tm->tm_hour > 12)
    {
      tm->tm_hour -= 12;
      strcpy(ampm_buffer, "PM");
    }
    else
    {
      strcpy(ampm_buffer, "AM");
    }
    sprintf (time_buffer, "%2d:%02d", tm->tm_hour, tm->tm_min);//, tm->tm_sec);
    gtk_label_set_text (GTK_LABEL (timeLabel), time_buffer);
    gtk_label_set_text (GTK_LABEL (ampmLabel), ampm_buffer);

    sprintf (date_buffer, "%2d/%02d", tm->tm_mon + 1, tm->tm_mday);
    gtk_label_set_text (GTK_LABEL (dateLabel), date_buffer);
    // gtk_label_set_text (GTK_LABEL (tempLabel), " 67");
    // gtk_label_set_text (GTK_LABEL (dayLabel), "MON");
    // TRACE_I("current time : (%llu) %04d-%02d-%02dT%02d:%02d:%02dZ", now,
    //   1900 + tm->tm_year, tm->tm_mon + 1, tm->tm_mday, );
}

int main(int argc, char* argv[]) {
  gtk_init(&argc, &argv);

  timeLabel = gtk_label_new("        ");
  ampmLabel = gtk_label_new("  ");
  dateLabel = gtk_label_new("     ");
  tempLabel = gtk_label_new(" 67");
  tempUnitsLabel = gtk_label_new("°F");
  dayLabel = gtk_label_new("MON");

  GdkRGBA red_color {1.0, .0, .0, 1.0};
  gtk_widget_override_color(timeLabel, GtkStateFlags::GTK_STATE_FLAG_NORMAL, &red_color);
  gtk_widget_override_color(ampmLabel, GtkStateFlags::GTK_STATE_FLAG_NORMAL, &red_color);
  gtk_widget_override_color(dateLabel, GtkStateFlags::GTK_STATE_FLAG_NORMAL, &red_color);
  gtk_widget_override_color(tempLabel, GtkStateFlags::GTK_STATE_FLAG_NORMAL, &red_color);
  gtk_widget_override_color(tempUnitsLabel, GtkStateFlags::GTK_STATE_FLAG_NORMAL, &red_color);
  gtk_widget_override_color(dayLabel, GtkStateFlags::GTK_STATE_FLAG_NORMAL, &red_color);

  PangoFontDescription *time_font_description = pango_font_description_new();
  pango_font_description_set_family(time_font_description, "DSEG14 Modern");
  pango_font_description_set_size(time_font_description, 300 * PANGO_SCALE);
  pango_font_description_set_weight(time_font_description, PangoWeight::PANGO_WEIGHT_BOLD);
  gtk_widget_override_font(timeLabel, time_font_description);

  PangoFontDescription *ampm_font_description = pango_font_description_new();
  pango_font_description_set_family(ampm_font_description, "DSEG14 Modern");
  pango_font_description_set_size(ampm_font_description, 24 * PANGO_SCALE);
  pango_font_description_set_weight(ampm_font_description, PangoWeight::PANGO_WEIGHT_BOLD);
  gtk_widget_override_font(ampmLabel, ampm_font_description);

  PangoFontDescription *date_font_description = pango_font_description_new();
  pango_font_description_set_family(date_font_description, "DSEG14 Modern");
  pango_font_description_set_size(date_font_description, 96 * PANGO_SCALE);
  pango_font_description_set_weight(date_font_description, PangoWeight::PANGO_WEIGHT_BOLD);
  gtk_widget_override_font(tempLabel, date_font_description);
  gtk_widget_override_font(dayLabel, date_font_description);
  gtk_widget_override_font(dateLabel, date_font_description);

  PangoFontDescription *temp_units_font_description = pango_font_description_new();
  pango_font_description_set_family(temp_units_font_description, "Arial");
  pango_font_description_set_size(temp_units_font_description, 24 * PANGO_SCALE);
  pango_font_description_set_weight(temp_units_font_description, PangoWeight::PANGO_WEIGHT_BOLD);
  gtk_widget_override_font(tempUnitsLabel, temp_units_font_description);
  
  grid = gtk_grid_new();
  gtk_grid_attach ( GTK_GRID ( grid ), ampmLabel, 0, 0, 1, 1 );
  gtk_grid_attach ( GTK_GRID ( grid ), timeLabel, 0, 0, 7, 25 );
  gtk_grid_attach ( GTK_GRID ( grid ), tempLabel, 8, 0, 1, 1 );
  gtk_grid_attach ( GTK_GRID ( grid ), tempUnitsLabel, 9, 0, 1, 1 );
  gtk_grid_attach ( GTK_GRID ( grid ), dayLabel, 8, 3, 1, 10 );
  gtk_grid_attach ( GTK_GRID ( grid ), dateLabel, 8, 13, 1, 10 );
  
  auto window = gtk_window_new(GtkWindowType::GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Hello world (label)");
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);
  g_signal_connect (window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);
  gtk_container_add ( GTK_CONTAINER ( window ), grid );
  GdkRGBA black_color {.0, .0, .0, 1.0};
  gtk_widget_override_background_color(window, GtkStateFlags::GTK_STATE_FLAG_NORMAL, &black_color);
  gtk_widget_show_all(window);

  timer = g_timeout_add (1000, UpdateTime, NULL);

  gtk_main();
}
