#include <gtk/gtk.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include "ForecastDayWidget.h"
#include "TopRow.h"
#include "BottomRow.h"
#include "CurlThread.h"
#include "ForecastParser.h"

static TopRow* topRow = nullptr;
static BottomRow* bottomRow = nullptr;
static GtkWidget* screen = nullptr;


int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);

    if (__cplusplus == 202101L) std::cout << "C++23";
    else if (__cplusplus == 202002L) std::cout << "C++20";
    else if (__cplusplus == 201703L) std::cout << "C++17";
    else if (__cplusplus == 201402L) std::cout << "C++14";
    else if (__cplusplus == 201103L) std::cout << "C++11";
    else if (__cplusplus == 199711L) std::cout << "C++98";
    else std::cout << "pre-standard C++." << __cplusplus;
    std::cout << "\n";

    if (argc < 2 || std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")
    {
        std::cout << "Usage " << argv[0] << " [options]" <<std::endl;
        std::cout << "    --forecastFile=<filename>   File path for the forecast json file from accuweather.com instead of doing a curl call" << std::endl;
        return 1;
    }
	std::vector<ForecastDayData> days;

    std::string arg1 = argv[1];
    auto index = arg1.find("--forecastFile=");
    if (index != std::string::npos)
    {
    	const std::string &forecastFileName = arg1.substr(index + 15);
		std::cout << "forecastFileName " << forecastFileName << std::endl;
		if (!forecastFileName.empty())
		{
			std::ifstream forecastFile(forecastFileName, std::ios::in);
			if (!forecastFile.is_open())
			{
				std::cout << "Could not open forecast file " << forecastFileName << std::endl;
				return 1;
			}
			days = ForecastParser::Parse(forecastFile);
		}
    }


    std::vector<CurlThreadConfig> config = {CurlThreadConfig("https://google.com", 20, 48, 00,
    		[&](std::string contents)
			{
    			std::cout << "Received contents: " << contents << std::endl;
			}) };
    CurlThread curlThread(config);
    curlThread.Start();

    // GtkCssProvider *provider = gtk_css_provider_new ();
    // gtk_css_provider_load_from_path (provider, "gtk-widgets.css", NULL);

    // GtkStyleContext *context = gtk_widget_get_style_context(timeLabel);
    // gtk_style_context_add_provider (context,
    // 								  GTK_STYLE_PROVIDER(provider),
    // 								  GTK_STYLE_PROVIDER_PRIORITY_USER);

    topRow = new TopRow();
    bottomRow = new BottomRow();

    screen = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start ( GTK_BOX(screen), topRow->Widget(), 0, 0, 0 );
    gtk_box_pack_start ( GTK_BOX(screen), bottomRow->Widget(), 0, 0, 0 );

  	auto window = gtk_window_new(GtkWindowType::GTK_WINDOW_TOPLEVEL);
  	gtk_window_set_title(GTK_WINDOW(window), "Hello world (label)");
  	gtk_window_set_default_size(GTK_WINDOW(window), 1024, 768);
  	g_signal_connect (window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);
    gtk_container_add ( GTK_CONTAINER ( window ), screen );
  	GdkRGBA black_color {.0, .0, .0, 1.0};
  	gtk_widget_override_background_color(window, GtkStateFlags::GTK_STATE_FLAG_NORMAL, &black_color);
  	gtk_widget_show_all(window);

	bottomRow->Update(days);

	gtk_main();
}

