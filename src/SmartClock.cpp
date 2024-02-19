#include <gtk/gtk.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include "ForecastDayWidget.h"
#include "TopRow.h"
#include "BottomRow.h"
#include "CurlThread.h"
#include "MqttThread.h"
#include "ForecastParser.h"
#include "log.h"

static TopRow* topRow = nullptr;
static BottomRow* bottomRow = nullptr;
static GtkWidget* screen = nullptr;


std::vector<ForecastDayData> days;
static gboolean HandleForecast(gpointer userdata)
{
    bottomRow->Update(days);
    return G_SOURCE_REMOVE;
}

static gboolean HandleGarageTemp(gpointer userdata)
{
    uintptr_t pValue = (uintptr_t)userdata;
    float value = *(float*)(&pValue);
    topRow->UpdateGarageTemp(value);
    return G_SOURCE_REMOVE;
}


int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);

    FILELog::ReportingLevel() = ldebug3;
    FILE* log_fd = fopen( "SmartClock.log", "w" );
    Output2FILE::Stream() = log_fd;

    if (__cplusplus == 202101L) FILE_LOG(linfo) << "C++23";
    else if (__cplusplus == 202002L) FILE_LOG(linfo) << "C++20";
    else if (__cplusplus == 201703L) FILE_LOG(linfo) << "C++17";
    else if (__cplusplus == 201402L) FILE_LOG(linfo) << "C++14";
    else if (__cplusplus == 201103L) FILE_LOG(linfo) << "C++11";
    else if (__cplusplus == 199711L) FILE_LOG(linfo) << "C++98";
    else FILE_LOG(linfo) << "pre-standard C++." << __cplusplus;
    FILE_LOG(linfo) << "\n";

    auto saveForecasts = false;
    if (argc >= 2)
    {
        if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")
        {
            std::cout << "Usage " << argv[0] << " [options]" <<std::endl;
            std::cout << "    --forecastFile=<filename>   File path for the forecast json file from accuweather.com instead of doing a curl call" << std::endl;
            std::cout << "    --saveForecasts             Writes the forecast json to files" << std::endl;
            return 1;
        }

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
        saveForecasts = (arg1.find("--saveForecasts") != std::string::npos);
    }

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

  	auto* window = gtk_window_new(GtkWindowType::GTK_WINDOW_TOPLEVEL);
  	gtk_window_set_title(GTK_WINDOW(window), "SmartClock");
  	gtk_window_set_default_size(GTK_WINDOW(window), 1024, 768);
  	g_signal_connect (window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);
    gtk_container_add ( GTK_CONTAINER ( window ), screen );
  	GdkRGBA black_color {.0, .0, .0, 1.0};
  	gtk_widget_override_background_color(window, GtkStateFlags::GTK_STATE_FLAG_NORMAL, &black_color);
  	gtk_widget_show_all(window);

	bottomRow->Update(days);

    CurlThread curlThread;
    // curlThread.AddUrlToRetrieve(CurlThreadConfig("https://google.com", 15, "urlContents", "html",
    // 		[&](std::string contents)
    //     {
    //         std::cout << "Received contents: " << contents << std::endl;
    //     }) );
    // curlThread.AddUrlToRetrieve(CurlThreadConfig("https://www.google.com", 15, "urlContents", "json",
    // 		[&](std::string contents)
    //     {
    //         std::cout << "Received contents: " << contents << std::endl;
    //     }) );
    CurlThreadConfig curlConfig(
        "http://dataservice.accuweather.com/forecasts/v1/daily/5day/332120?apikey=E73cA2eAoUBJBCtEGvmSZamye4fl11ae&details=true",
        30*60,
        (saveForecasts ? "urlContents" : ""), 
        "json",
        [&](std::string contents)
        {
            std::cout << "Received weather contents: " << std::endl;//contents << std::endl;
            days = ForecastParser::Parse(contents);
            gdk_threads_add_idle(HandleForecast, nullptr);
        }
    );
    curlThread.AddUrlToRetrieve(curlConfig);        
    curlThread.Start();

    MqttThread mqttThread([&](float garageTemp)
    {
        std::cout << "Received garage temp contents: " << garageTemp << std::endl;
        uintptr_t value = *(uint32_t*)(&garageTemp);
        gdk_threads_add_idle(HandleGarageTemp, (void*)value);
    });
    mqttThread.Start();

    gtk_window_fullscreen(GTK_WINDOW(window));

    try
    {
	    gtk_main();
    }
    catch(const std::exception& e)
    {
        FILE_LOG(lerror) << "Exception thrown" << e.what() << std::endl;
    }
}

