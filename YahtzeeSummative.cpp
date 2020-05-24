//Dylan - Yahtzee Summative
//Yahtzee Game Summative

#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_video.h>

struct uSettings {
    int SCREEN_W;
    int SCREEN_H;
    float FPS;
};

uSettings prevSettings () { //Reads in user settings
    FILE *userSettings = fopen("UserSettings.txt", "r+");
    uSettings settings;

    fscanf(userSettings, "SCREEN_W = %d\nSCREEN_H = %d\nFPS = %f", &settings.SCREEN_W, &settings.SCREEN_H, &settings.FPS);
    fclose(userSettings);
    return settings;
}

int main () {
    //Initializes Allegro Functions
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_install_mouse();

    bool exit = false, draw = true;

    uSettings options; //Calls upon uSettings Struct
    options = prevSettings(); //Calls upon prevSettings function to read in current user settings

    ALLEGRO_DISPLAY *display = al_create_display(options.SCREEN_W, options.SCREEN_H);
    ALLEGRO_TIMER *timer = al_create_timer(1 / options.FPS);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

    ALLEGRO_EVENT events;

    al_set_window_title(display, "Yahtzee V0.0.1");
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_start_timer(timer);
    while (!exit) {
        if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            exit = true;
        }
        if (events.type == ALLEGRO_EVENT_TIMER) {
            if (draw) {
                draw = false;
                al_flip_display();
            }
        }
    }

    al_destroy_timer(timer);
    al_shutdown_video_addon();
    al_destroy_display(display);
    return 0;
}
