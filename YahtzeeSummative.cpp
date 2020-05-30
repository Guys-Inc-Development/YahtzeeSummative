// Dylan - Yahtzee Summative
// Yahtzee Game Summative

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_video.h>

// Enum to save screenstate
enum screenState {
	Title = 1,
	Paused = 2,
	Playing = 3,
	Options = 4,
} screen;

// User settings struct
struct uSettings {
	int SCREEN_W;
	int SCREEN_H;
	float FPS;
};

// Reads in user settings from file and stores them in struct
uSettings prevSettings() { //Reads in user settings
	FILE* userSettings = fopen("UserSettings.txt", "r+");
	uSettings options;
	fscanf(userSettings, "SCREEN_W = %d\nSCREEN_H = %d\nFPS = %f", &options.SCREEN_W, &options.SCREEN_H, &options.FPS);
	fclose(userSettings);
	return options;
}

// Plays titlescreen Video
void playVideo(ALLEGRO_DISPLAY *display, ALLEGRO_VIDEO *video) {
	ALLEGRO_BITMAP *frame = al_get_video_frame(video);
	if (!frame) 
		return;
	al_draw_scaled_bitmap(frame, 0, 0, al_get_bitmap_width(frame), al_get_bitmap_height(frame), 0, 0, al_get_display_width(display), al_get_display_height(display), NULL);
}


// Function to show mouse position in console
void mousePos (int mouseX, int mouseY) {
	printf("%d %d", mouseX, mouseY);
	system("cls");
}

int main() {
	// Initializes Allegro Functions
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_init_video_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();
	al_install_audio();
	al_reserve_samples(1);

	// Read in user settings
	uSettings options;         // Calls upon uSettings Struct
	options = prevSettings();  // Calls upon prevSettings function to read in current user settings

	// Initialize Essential Allegro Elements
	ALLEGRO_DISPLAY *display = al_create_display(options.SCREEN_W, options.SCREEN_H);
	ALLEGRO_TIMER *timer = al_create_timer(1 / options.FPS);
	ALLEGRO_TIMER *playButtonAppear = al_create_timer(3);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_EVENT events;

	// Initialize Non-essential Allegro Elements
	ALLEGRO_VIDEO *titlescreen = al_open_video("Yahtzee0001-7198.ogv");
	ALLEGRO_VIDEO *playingBG = al_open_video("Playing Background.ogv");
	ALLEGRO_BITMAP *pause = al_load_bitmap("Paused Screen.png");
	ALLEGRO_FONT *text54 = al_load_font("Montserrat-ExtraBold.ttf", 54, ALLEGRO_ALIGN_CENTER);
	ALLEGRO_FONT *text24 = al_load_font("Montserrat-ExtraBold.ttf", 24, NULL);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR red = al_map_rgb(230, 60, 56);
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	al_set_window_title(display, "Yahtzee V0.0.5");

	// Register Events Sources
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(playButtonAppear));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_video_event_source(titlescreen));
	al_register_event_source(event_queue, al_get_video_event_source(playingBG));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	// Initialize Standard Variables
	bool exit = false, draw = true, showPlayButton = false, uno = false;
	int mouseX = 0, mouseY = 0, titleFade = 0;
	screen = Title;

	// Begin Game Loop
	al_start_video(titlescreen, al_get_default_mixer());
	al_start_video(playingBG, al_get_default_mixer());
	al_set_video_playing(playingBG, false);
	al_start_timer(playButtonAppear);
	al_start_timer(timer);
	while (!exit) {
		al_wait_for_event(event_queue, &events);

		// Exits if user closes display window
		if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit = true;
		}
		// Checks for mouse movement
		if (events.type == ALLEGRO_EVENT_MOUSE_AXES) {
			mouseX = events.mouse.x;
			mouseY = events.mouse.y;
			if (screen == Title && showPlayButton == true) {
				if (mouseX >= options.SCREEN_W * 0.2 && mouseY >= options.SCREEN_H * 0.8 && mouseX <= options.SCREEN_W * 0.2 + 200 && mouseY <= options.SCREEN_H * 0.8 + 100) {
					al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				} else if (mouseX >= options.SCREEN_W * 0.65 && mouseY >= options.SCREEN_H * 0.8 && mouseX <= options.SCREEN_W * 0.65 + 200 && mouseY <= options.SCREEN_H * 0.8 + 100) {
					al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				} else {
					al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
				}
			} else if (screen == Paused) {
				if (mouseX >= 50 && mouseX <= 200 && mouseY >= 150 && mouseY <= 205) {
					al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				} else if (mouseX >= 50 && mouseX <= 320 && mouseY >= 250 && mouseY <= 305) {
					al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				} else if (mouseX >= 50 && mouseX <= 480 && mouseY >= 350 && mouseY <= 405) {
					al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				} else if (mouseX >= 50 && mouseX <= 580 && mouseY >= 450 && mouseY <= 505) {
					al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				} else {
					al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
				}
			} else {
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
			}
		}
		// Checks for mouse clicks
		if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (events.mouse.button & 1) {
				if (screen == Title && showPlayButton == true) {  // If buttons are met, and mouse is clicked, checks if mouse clicked the button, and acts accordingly
					if (mouseX >= options.SCREEN_W * 0.2 && mouseY >= options.SCREEN_H * 0.8 && mouseX <= options.SCREEN_W * 0.2 + 200 && mouseY <= options.SCREEN_H * 0.8 + 100) {
						screen = Playing;
						al_set_video_playing(titlescreen, false);
						al_set_video_playing(playingBG, true);
						draw = true;
					} else if (mouseX >= options.SCREEN_W * 0.65 && mouseY >= options.SCREEN_H * 0.8 && mouseX <= options.SCREEN_W * 0.65 + 200 && mouseY <= options.SCREEN_H * 0.8 + 100) {
						exit = true;
					}
				} else if (screen == Paused) { // Pause screen buttons
					if (mouseX >= 50 && mouseX <= 200 && mouseY >= 150 && mouseY <= 205) { // Play
						screen = Playing;
						draw = true;
					} else if (mouseX >= 50 && mouseX <= 320 && mouseY >= 250 && mouseY <= 305) { // Options
						screen = Options;
						draw = true;
					} else if (mouseX >= 50 && mouseX <= 465 && mouseY >= 350 && mouseY <= 405) { // Quit to menu
						screen = Title;
						titleFade = 0;
						showPlayButton = false;
						al_seek_video(titlescreen, 0);
						al_set_video_playing(titlescreen, true);
						al_resume_timer(playButtonAppear);
						al_clear_to_color(black);
						draw = true;
					} else if (mouseX >= 50 && mouseX <= 580 && mouseY >= 450 && mouseY <= 505) { // Quit to desktop
						exit = true;
						break;
					}
				}
			}
		}
		// Checks for keyboard events
		if (events.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (events.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				if (screen == Playing) {
					screen = Paused;
					al_set_video_playing(playingBG, false);
					uno = true;
					draw = true;
				} else if (screen == Paused) {
					screen = Playing;
					al_set_video_playing(playingBG, true);
					draw = true;
				}
				break;
			}
		}
		// Bascially just the title screen
		if (events.type == ALLEGRO_EVENT_VIDEO_FRAME_SHOW) {
			if (events.type == ALLEGRO_EVENT_VIDEO_FINISHED) {
				if (screen == Title) {
					al_seek_video(titlescreen, 0);
				} else if (screen == Playing) {
					al_seek_video(playingBG, 0);
				}
				al_clear_to_color(black);
				draw = true;
			} else {
				if (screen == Title) {
					playVideo(display, titlescreen); // I hate the video addon
					if (showPlayButton == true) { // Draws buttons
						al_draw_filled_rounded_rectangle(options.SCREEN_W * 0.2, options.SCREEN_H * 0.8, options.SCREEN_W * 0.2 + 200, options.SCREEN_H * 0.8 + 100, 15, 15, al_map_rgba(230, 60, 56, titleFade));
						al_draw_text(text54, al_map_rgba(255, 255, 255, titleFade), options.SCREEN_W * 0.2 + 100, options.SCREEN_H * 0.8 + 15, ALLEGRO_ALIGN_CENTER, "PLAY");
						al_draw_filled_rounded_rectangle(options.SCREEN_W * 0.65, options.SCREEN_H * 0.8, options.SCREEN_W * 0.65 + 200, options.SCREEN_H * 0.8 + 100, 15, 15, al_map_rgba(230, 60, 56, titleFade));
						al_draw_text(text54, al_map_rgba(255, 255, 255, titleFade), options.SCREEN_W * 0.65 + 100, options.SCREEN_H * 0.8 + 15, ALLEGRO_ALIGN_CENTER, "QUIT");
						if (titleFade < 255) {
							titleFade += 5;
						}
					}
				} else if (screen == Playing) {
					playVideo(display, playingBG);
				} 
				draw = true;
			}
		}
		// Checks for timer events
		if (events.type == ALLEGRO_EVENT_TIMER) {
			if (events.timer.source == timer) {
				if (draw) {
					if (screen == Playing) {
						al_draw_text(text54, white, 0, 0, NULL, "");
					} else if (screen == Paused) {
						if (uno) {
							al_draw_scaled_bitmap(pause, 0, 0, 1920, 1080, 0, 0, options.SCREEN_W, options.SCREEN_H, NULL);
							uno = false;
						}
						al_draw_text(text54, white, 50, 150, NULL, "PLAY");
						al_draw_text(text54, white, 50, 250, NULL, "OPTIONS");
						al_draw_text(text54, white, 50, 350, NULL, "QUIT TO MENU");
						al_draw_text(text54, white, 50, 450, NULL, "QUIT TO DESKTOP");
					}
					draw = false;
					al_flip_display();
				}
			} else if (events.timer.source == playButtonAppear) {
				showPlayButton = true;
				al_stop_timer(playButtonAppear);
			}
		}
	}

	printf("Ending...");

	// Prevents memory leaks
	al_close_video(titlescreen);
	al_shutdown_image_addon();
	al_shutdown_video_addon();
	al_shutdown_font_addon();
	al_shutdown_ttf_addon();
	al_shutdown_native_dialog_addon();
	al_shutdown_primitives_addon();
	al_destroy_timer(timer);
	al_destroy_display(display);
	return 0;
}
