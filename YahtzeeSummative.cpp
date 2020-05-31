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
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

// Enum to save screenstate
enum screenState {
	Title = 1,
	Paused = 2,
	GamePick = 3,
	GameOptions = 4,
	Playing = 5,
	Options = 6,
} screen;

// User settings struct
struct uSettings {
	int SCREEN_W = 1280;
	int SCREEN_H = 720;
	float FPS = 60.0;
	float SOUND_EFFECTS = 1.0;
	float MUSIC = 1.0;
};

// Reads in user settings from file and stores them in struct
uSettings prevSettings() { //Reads in user settings
	FILE* userSettings = fopen("UserSettings.txt", "r");
	uSettings options;
	fscanf(userSettings, "SCREEN_W = %d\nSCREEN_H = %d\nFPS = %f\nSOUND_EFFECTS = %f\nMUSIC = %f", &options.SCREEN_W, &options.SCREEN_H, &options.FPS, &options.SOUND_EFFECTS, &options.MUSIC);
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

void buttonCheck(ALLEGRO_DISPLAY *display, int mouseX, int mouseY, bool showPlayButton, int sliderX[3]) {
	uSettings options;
	if (screen == Title && showPlayButton == true) {
		if (mouseX >= options.SCREEN_W * 0.2 && mouseY >= options.SCREEN_H * 0.8 && mouseX <= options.SCREEN_W * 0.2 + 200 && mouseY <= options.SCREEN_H * 0.8 + 100) {
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else if (mouseX >= options.SCREEN_W * 0.65 && mouseY >= options.SCREEN_H * 0.8 && mouseX <= options.SCREEN_W * 0.65 + 200 && mouseY <= options.SCREEN_H * 0.8 + 100) {
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else {
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
		}
	} else if (screen == Paused) {
		if (mouseX >= 50 && mouseX <= 205 && mouseY >= 150 && mouseY <= 205) {
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
	} else if (screen == GamePick) {
		if (mouseX >= 150 && mouseX <= 345 && mouseY >= 210 && mouseY <= 535) { // Play
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else if (mouseX >= 400 && mouseX <= 600 && mouseY >= 210 && mouseY <= 535) { // Online
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else if (mouseX >= 660 && mouseX <= 858 && mouseY >= 210 && mouseY <= 535) { // Game Settings
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else if (mouseX >= 913 && mouseX <= 1110 && mouseY >= 210 && mouseY <= 535) { // Options
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else {
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
		}
	} else if (screen == Options) {
		if (mouseX >= sliderX[0] + 492 && mouseX <= sliderX[0] + 492 + 30 && mouseY >= 306 && mouseY <= 319) { // FPS
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else if (mouseX >= sliderX[1] && mouseX <= sliderX[1] + 492 + 30 && mouseY >= 336 && mouseY <= 349) { // Sound Volume
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else if (mouseX >= sliderX[2] && mouseX <= sliderX[2] + 492 + 30 && mouseY >= 366 && mouseY <= 379) { // Music Volume
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else if (mouseX >= 942 && mouseX <= 1200 && mouseY >= 418 && mouseY <= 553) { // Save
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else if (mouseX >= 943 && mouseX <= 1200 && mouseY >= 360 && mouseY <= 676) { // Cancel
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK); 
		} else if (mouseX >= 747 && mouseX <= 913 && mouseY >= 603 && mouseY <= 676) {
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK); 
		} else {
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
		}
	} else {
		al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	}
}


// Function to show mouse position in console
void mousePos (int mouseX, int mouseY) {
	printf("%d %d\n", mouseX, mouseY);
}

int main() {
	// Initializes Allegro Functions
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_init_video_addon();
	al_init_primitives_addon();
	al_init_acodec_addon();
	al_install_keyboard();
	al_install_mouse();
	al_install_audio();
	al_reserve_samples(2);

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
	ALLEGRO_BITMAP *gamemode = al_load_bitmap("Gamemode Screen.png");
	ALLEGRO_BITMAP *optionsScreen = al_load_bitmap("Options Screen.png");
	ALLEGRO_BITMAP *optionSlider = al_load_bitmap("Options Slider Button.png");
	ALLEGRO_SAMPLE *error = al_load_sample("Error Sound Effect.mp3");
	ALLEGRO_FONT *text54 = al_load_font("Montserrat-ExtraBold.ttf", 54, ALLEGRO_ALIGN_CENTER);
	ALLEGRO_FONT *text24 = al_load_font("Montserrat-ExtraBold.ttf", 24, NULL);
	ALLEGRO_FONT *text16 = al_load_font("Montserrat-ExtraBold.ttf", 16, NULL);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR red = al_map_rgb(230, 60, 56);
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	al_set_window_title(display, "Yahtzee V0.0.6");

	// Register Events Sources
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(playButtonAppear));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_video_event_source(titlescreen));
	al_register_event_source(event_queue, al_get_video_event_source(playingBG));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	// Initialize Standard Variables
	bool exit = false, draw = true, showPlayButton = false, uno = false, sliderToggle[3] = {false, false, false};
	int mouseX = 0, mouseY = 0, titleFade = 0, sliderX[3] = {0, 0, 0}, mouseOffsetX = 0, sliderMoved[3] = {0, 0, 0};
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
			buttonCheck(display, mouseX, mouseY, showPlayButton, sliderX);
			if (screen == Options) {
				if (sliderToggle[0] == true) {
					sliderX[0] = mouseX - mouseOffsetX + sliderMoved[0];
					if (sliderX[0] <= -145) {
						sliderX[0] = -145;
					} else if (sliderX[0] >= 82) {
						sliderX[0] = 82;
					} 
					draw = true;
				} else if (sliderToggle[1] == true) {
					sliderX[1] = mouseX - mouseOffsetX + sliderMoved[1];
					if (sliderX[1] <= -112) {
						sliderX[1] = -112;
					} else if (sliderX[1] >= 115) {
						sliderX[1] = 115;
					}
					draw = true;
				} else if (sliderToggle[2] == true) {
					sliderX[2] = mouseX - mouseOffsetX + sliderMoved[2];
					if (sliderX[2] <= -112) {
						sliderX[2] = -112;
					} else if (sliderX[2] >= 115) {
						sliderX[2] = 115;
					}
					draw = true;
				}
			}
		}
		// Checks for mouse clicks
		if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (events.mouse.button & 1) {
				if (screen == Title && showPlayButton == true) {  // If buttons are met, and mouse is clicked, checks if mouse clicked the button, and acts accordingly
					if (mouseX >= options.SCREEN_W * 0.2 && mouseY >= options.SCREEN_H * 0.8 && mouseX <= options.SCREEN_W * 0.2 + 200 && mouseY <= options.SCREEN_H * 0.8 + 100) {
						screen = GamePick;
						al_set_video_playing(titlescreen, false);
						al_set_video_playing(playingBG, true);
						draw = true;
					} else if (mouseX >= options.SCREEN_W * 0.65 && mouseY >= options.SCREEN_H * 0.8 && mouseX <= options.SCREEN_W * 0.65 + 200 && mouseY <= options.SCREEN_H * 0.8 + 100) {
						exit = true;
					}
				} else if (screen == Paused) { // Pause screen buttons
					if (mouseX >= 50 && mouseX <= 205 && mouseY >= 150 && mouseY <= 205) { // Play
						screen = Playing;
						al_set_video_playing(playingBG, true);
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
				} else if (screen == GamePick) {
					if (mouseX >= 150 && mouseX <= 345 && mouseY >= 210 && mouseY <= 535) { // Local Multiplayer
						screen = Playing;
						al_seek_video(playingBG, 0);
						draw = true;
					} else if (mouseX >= 400 && mouseX <= 600 && mouseY >= 210 && mouseY <= 535) { // Online Multiplayer
						al_play_sample(error, options.SOUND_EFFECTS, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
					} else if (mouseX >= 660 && mouseX <= 858 && mouseY >= 210 && mouseY <= 535) { // Gamemode select
						screen = GameOptions;
					} else if (mouseX >= 913 && mouseX <= 1110 && mouseY >= 210 && mouseY <= 535) { //Options
						screen = Options;
						draw = true;
					} 
				} else if (screen == Options) {
					if (mouseX >= sliderX[0] + 492 && mouseX <= sliderX[0] + 492 + 30 && mouseY >= 306 && mouseY <= 319) { // Slider 1
						sliderToggle[0] = true;
						mouseOffsetX = mouseX;
						al_hide_mouse_cursor(display);
					} else if (mouseX >= sliderX[1] && mouseX <= sliderX[1] + 492 + 30 && mouseY >= 336 && mouseY <= 349) { // Slider 2
						sliderToggle[1] = true;
						mouseOffsetX = mouseX;
						al_hide_mouse_cursor(display);
					} else if (mouseX >= sliderX[2] && mouseX <= sliderX[2] + 492 + 30 && mouseY >= 366 && mouseY <= 379) { // Slider 3
						sliderToggle[2] = true;
						mouseOffsetX = mouseX;
						al_hide_mouse_cursor(display);
					} else if (mouseX >= 944 && mouseX <= 1200 && mouseY >= 420 && mouseY <= 533) { // Save
						screen = GamePick;
						FILE *settings = fopen("UserSettings.txt", "w");
						fprintf(settings, "SCREEN_W = 1280\nSCREEN_H = 720\nFPS = %.0f.0\nSOUND_EFFECTS = %f\nMUSIC = %f", options.FPS + sliderX[0] * 0.249, options.SOUND_EFFECTS + sliderX[1] * 0.0085, options.MUSIC + sliderX[1] * 0.0085);
						fclose(settings);
						options = prevSettings();
						draw = true;
					} else if (mouseX >= 747 && mouseX <= 913 && mouseY >= 603 && mouseY <= 676) { // Reset
						FILE *settings = fopen("UserSettings.txt", "w");
						fprintf(settings, "SCREEN_W = 1280\nSCREEN_H = 720\nFPS = 60\nSOUND_EFFECTS = 1.0\nMUSIC = 1.0");
						fclose(settings);
						for (int i = 0; i < 3; i++) {
							sliderX[i] = 0;
						}
						mouseOffsetX = 0;
						options = prevSettings();
						draw = true;
					} else if (mouseX >= 944 && mouseX <= 1200 && mouseY >= 560 && mouseY <= 676) { // Cancel
						screen = GamePick;
						draw = true;
					}
				}
			}
		} else if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			if (screen == Options) {
				if (sliderToggle[0] == true) {
					sliderToggle[0] = false;
					sliderMoved[0] = mouseX - 492;
					al_show_mouse_cursor(display);
				} else if (sliderToggle[1] == true) {
					sliderToggle[1] = false;
					sliderMoved[1] = mouseX - 492;
					al_show_mouse_cursor(display);
				} else if (sliderToggle[2] == true) {
					sliderToggle[2] = false;
					sliderMoved[2] = mouseX - 492;
					al_show_mouse_cursor(display);
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
				} else if (screen == GamePick) {
					screen = Title;
					titleFade = 0;
					showPlayButton = false;
					al_set_video_playing(playingBG, false);
					al_seek_video(titlescreen, 0);
					al_set_video_playing(titlescreen, true);
					al_resume_timer(playButtonAppear);
					al_clear_to_color(black);
					draw = true;
				} else if (screen == GameOptions) {
					screen = GamePick;
					draw = true;
				}
				break;
			}
		}
		// Repeats videos if they finish
		if (events.type == ALLEGRO_EVENT_VIDEO_FINISHED) {
			if (screen == Title) {
				al_seek_video(titlescreen, 0);
				al_set_video_playing(titlescreen, true);
			} else if (screen == Playing || screen == GamePick || screen == Options) {
				al_seek_video(playingBG, 0);
				al_set_video_playing(playingBG, true);
			}
		}
		// Plays the videos
		if (events.type == ALLEGRO_EVENT_VIDEO_FRAME_SHOW) {
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
			} else if (screen == Playing || screen == GamePick || screen == Options) {
				playVideo(display, playingBG);
			} 
			draw = true;
		}
		// Checks for timer events
		if (events.type == ALLEGRO_EVENT_TIMER) {
			if (events.timer.source == timer) {
				if (draw) {
					if (screen == GamePick) {
						al_draw_scaled_bitmap(gamemode, 0, 0, 2560, 1440, 0, 0, options.SCREEN_W, options.SCREEN_H, NULL);
					} else if (screen == Paused) {
						if (uno) {
							al_draw_scaled_bitmap(pause, 0, 0, 1920, 1080, 0, 0, options.SCREEN_W, options.SCREEN_H, NULL);
							al_draw_text(text54, white, 50, 150, NULL, "PLAY");
							al_draw_text(text54, white, 50, 250, NULL, "OPTIONS");
							al_draw_text(text54, white, 50, 350, NULL, "QUIT TO MENU");
							al_draw_text(text54, white, 50, 450, NULL, "QUIT TO DESKTOP");
							uno = false;
						}
					} else if (screen == Options) {
						al_draw_scaled_bitmap(optionsScreen, 0, 0, 1920, 1080, 0, 0, options.SCREEN_W, options.SCREEN_H, NULL); // Card
						al_draw_textf(text16, black, 245, 243, NULL, "%d", options.SCREEN_W); 
						al_draw_textf(text16, black, 245, 274, NULL, "%d", options.SCREEN_H);
						al_draw_textf(text16, black, 245, 305, NULL, "%.0f.0", options.FPS + sliderX[0] * 0.249);
						al_draw_scaled_bitmap(optionSlider, 0, 0, 1920, 1080, sliderX[0] - 3, 0, options.SCREEN_W, options.SCREEN_H, NULL); // Slider 1
						al_draw_textf(text16, black, 245, 335, NULL, "%.1f", options.SOUND_EFFECTS + sliderX[1] * 0.0085);
						al_draw_scaled_bitmap(optionSlider, 0, 0, 1920, 1080, sliderX[1] - 35, 30, options.SCREEN_W, options.SCREEN_H, NULL); // Slider 2
						al_draw_textf(text16, black, 245, 365, NULL, "%.1f", options.MUSIC + sliderX[2] * 0.0085);
						al_draw_scaled_bitmap(optionSlider, 0, 0, 1920, 1080, sliderX[2] - 35, 60, options.SCREEN_W, options.SCREEN_H, NULL); // Slider 3
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
	al_close_video(playingBG);
	al_destroy_bitmap(pause);
	al_destroy_bitmap(gamemode);
	al_destroy_sample(error);
	al_shutdown_image_addon();
	al_shutdown_video_addon();
	al_shutdown_font_addon();
	al_shutdown_ttf_addon();
	al_uninstall_audio();
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_shutdown_native_dialog_addon();
	al_shutdown_primitives_addon();
	al_destroy_timer(timer);
	al_destroy_display(display);
	return 0;
}
