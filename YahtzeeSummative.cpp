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
#include <time.h>

// Enum to save screenstate
enum screenState {
	Title = 1,
	Paused = 2,
	GamePick = 3,
	GameOptions = 4,
	Playing = 5,
	Options = 6,
	gameSetup = 7,
	Scoring = 8,
} screen;

// User settings struct
struct uSettings {
	int SCREEN_W = 1280;
	int SCREEN_H = 720;
	float FPS = 60.0;
	float SOUND_EFFECTS = 1.0;
	float MUSIC = 1.0;
};

struct playerScore {
	int ONES[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int TWOS[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int THREES[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int FOURS[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int FIVES[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int SIXES[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int OFKIND_THREE[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int OFKIND_FOUR[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int FULL_HOUSE[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int STRAIGHT_SMALL[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int STRAIGHT_LARGE[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int YAHTZEE[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int CHANCE[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	bool FILLED[8][13] = {{false, false, false, false, false, false, false, false, false, false, false, false, false}, 
						{false, false, false, false, false, false, false, false, false, false, false, false, false}, 
						{false, false, false, false, false, false, false, false, false, false, false, false, false},
						{false, false, false, false, false, false, false, false, false, false, false, false, false},
						{false, false, false, false, false, false, false, false, false, false, false, false, false}, 
						{false, false, false, false, false, false, false, false, false, false, false, false, false}, 
						{false, false, false, false, false, false, false, false, false, false, false, false, false}, 
						{false, false, false, false, false, false, false, false, false, false, false, false, false}};
};

// Reads in user settings from file and stores them in struct
uSettings prevSettings() { //Reads in user settings
	FILE* userSettings = fopen("./assets/UserSettings.txt", "r");
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

int buttonCheck(ALLEGRO_DISPLAY *display, int mouseX, int mouseY, bool showPlayButton, int sliderX[3], int currentPlayer, playerScore *score) {
	uSettings options;
	int box = 0;
	if (screen == Title && showPlayButton) {
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
		if (mouseX >= sliderX[0] + 492 - 30 && mouseX <= sliderX[0] + 492 && mouseY >= 246 && mouseY <= 259) { // SCREEN W
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else if (mouseX >= sliderX[1] + 492 - 30 && mouseX <= sliderX[1] + 492 && mouseY >= 276 && mouseY <= 289) { // SCREEN H
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else if (mouseX >= sliderX[2] + 492 && mouseX <= sliderX[2] + 492 + 30 && mouseY >= 306 && mouseY <= 319) { // FPS
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else if (mouseX >= sliderX[3] + 492 - 30 && mouseX <= sliderX[3] + 492 && mouseY >= 336 && mouseY <= 349) { // Sound Volume
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else if (mouseX >= sliderX[4] + 492 - 30 && mouseX <= sliderX[4] + 492 && mouseY >= 366 && mouseY <= 379) { // Music Volume
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
	} else if (screen == gameSetup) {
		if (mouseX >= 85 && mouseX <= 193 && mouseY >= 238 && mouseY <= 348) { // Add Players
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK); 
		} else if (mouseX >= 1083 && mouseX <= 1194 && mouseY >= 238 && mouseY <= 348) { // Remove Players
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else if (mouseX >= 34 && mouseX <= 146 && mouseY >= 34 && mouseY <= 95) { // Go Back
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else if (mouseX >= 976 && mouseX <= 1236 && mouseY >= 564 && mouseY <= 679) { // Play
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else {
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
		}
	} else if (screen == Playing) {
		if (mouseX >= 994 && mouseY >= 580 && mouseX <= 1248 && mouseY <= 694) { // End Turn
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else if (mouseX >= options.SCREEN_W / 2 - 62.5 - 300 && mouseY >= options.SCREEN_H / 2 - 62.5 && mouseX <= options.SCREEN_W / 2 + 62.5 - 300 && mouseY <= options.SCREEN_H / 2 + 62.5) { // Die 1
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else if (mouseX >= options.SCREEN_W / 2 - 62.5 - 150 && mouseY >= options.SCREEN_H / 2 - 62.5 && mouseX <= options.SCREEN_W / 2 + 62.5 - 150 && mouseY <= options.SCREEN_H / 2 + 62.5) { // Die 2
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else if (mouseX >= options.SCREEN_W / 2 - 62.5 && mouseY >= options.SCREEN_H / 2 - 62.5 && mouseX <= options.SCREEN_W / 2 + 62.5 && mouseY <= options.SCREEN_H / 2 + 62.5) { // Die 3
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else if (mouseX >= options.SCREEN_W / 2 - 62.5 + 150 && mouseY >= options.SCREEN_H / 2 - 62.5 && mouseX <= options.SCREEN_W / 2 + 62.5 + 150 && mouseY <= options.SCREEN_H / 2 + 62.5) { // Die 4
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else if (mouseX >= options.SCREEN_W / 2 - 62.5 + 300 && mouseY >= options.SCREEN_H / 2 - 62.5 && mouseX <= options.SCREEN_W / 2 + 62.5 + 300 && mouseY <= options.SCREEN_H / 2 + 62.5) { // Die 5
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else {
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
		}
	} else if (screen == Scoring) {
		if (mouseX >= 413 && mouseY >= 128 && mouseX <= 460 && mouseY <= 151) { // Ones
			if (!score->FILLED[currentPlayer - 1][0]) {
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				box = 1;
			}
		} else if (mouseX >= 413 && mouseY >= 153 && mouseX <= 460 && mouseY <= 176) { // Twos
			if (!score->FILLED[currentPlayer - 1][1]) {
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				box = 2;
			}
		} else if (mouseX >= 413 && mouseY >= 178 && mouseX <= 460 && mouseY <= 201) { // Threes
			if (!score->FILLED[currentPlayer - 1][2]) {
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				box = 3;
			}
		} else if (mouseX >= 413 && mouseY >= 203 && mouseX <= 460 && mouseY <= 226) { // Fours
			if (!score->FILLED[currentPlayer - 1][3]) {
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				box = 4;
			}
		} else if (mouseX >= 413 && mouseY >= 228 && mouseX <= 460 && mouseY <= 251) { // Fives
			if (!score->FILLED[currentPlayer - 1][4]) {
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				box = 5;
			}
		} else if (mouseX >= 413 && mouseY >= 253 && mouseX <= 460 && mouseY <= 276) { // Sixes
			if (!score->FILLED[currentPlayer - 1][5]) {
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				box = 6;
			}
		} else if (mouseX >= 413 && mouseY >= 388 && mouseX <= 460 && mouseY <= 411) { // 3 of a kind
			if (!score->FILLED[currentPlayer - 1][6]) {
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				box = 7;
			}
		} else if (mouseX >= 413 && mouseY >= 413 && mouseX <= 460 && mouseY <= 436) { // 4 of a kind
			if (!score->FILLED[currentPlayer - 1][7]) {
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				box = 8;
			}
		} else if (mouseX >= 413 && mouseY >= 438 && mouseX <= 460 && mouseY <= 461) { // Full House
			if (!score->FILLED[currentPlayer - 1][8]) {
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				box = 9;
			}
		} else if (mouseX >= 413 && mouseY >= 463 && mouseX <= 460 && mouseY <= 486) { // Small Straight
			if (!score->FILLED[currentPlayer - 1][9]) {
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				box = 10;
			}
		} else if (mouseX >= 413 && mouseY >= 488 && mouseX <= 460 && mouseY <= 511) { // Large Straight
			if (!score->FILLED[currentPlayer - 1][10]) {
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				box = 11;
			}
		} else if (mouseX >= 413 && mouseY >= 513 && mouseX <= 460 && mouseY <= 536) { // Yahtzee
			if (!score->FILLED[currentPlayer - 1][11]) {
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				box = 12;
			}
		} else if (mouseX >= 413 && mouseY >= 538 && mouseX <= 460 && mouseY <= 561) { // Chance
			if (!score->FILLED[currentPlayer - 1][12]) {
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				box = 13;
			}
		} else if (mouseX >= 994 && mouseY >= 580 && mouseX <= 1248 && mouseY <= 694) { // End Turn
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		} else {
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
			box = 0;
		}
	} else {
		al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	}
	return box;
}

int diceRoll(int max, int min) { // A bit of a useless function, but nontheless
	return rand() % max + min;;
}


int scoreCalculations (playerScore *score, int num1, int num2, int num3, int num4, int num5, ALLEGRO_FONT *text16, ALLEGRO_COLOR black, ALLEGRO_COLOR gray, int selectedBox, int currentPlayer, bool save) {
	int diceNum[5] = {num1, num2, num3, num4, num5}, 
	finalValue[14] = {score->ONES[currentPlayer - 1], score->TWOS[currentPlayer - 1], score->THREES[currentPlayer - 1], score->FOURS[currentPlayer - 1], score->FIVES[currentPlayer - 1], score->SIXES[currentPlayer - 1], score->OFKIND_THREE[currentPlayer - 1], score->OFKIND_FOUR[currentPlayer - 1], score->FULL_HOUSE[currentPlayer - 1], score->STRAIGHT_SMALL[currentPlayer - 1], score->STRAIGHT_LARGE[currentPlayer - 1], score->YAHTZEE[currentPlayer - 1], score->CHANCE[currentPlayer - 1], 0}, 
	matches[6] = {0, 0, 0, 0, 0, 0}, upper = 128;
	bool foundNums[6] = {false, false, false, false, false, false};

	// Upper Section
	for (int i = 0; i < 6; i++) { // Counts matches of every number
		for (int j = 0; j < 5; j++) {
			if (diceNum[j] == i + 1) {
				matches[i]++;
			}
		}
		finalValue[i] = matches[i] * (i + 1); // Ones to Sixes
	}

	// Lower section
	for (int i = 0; i < 6; i++) {
		if (matches[i] == 3) { 
			for (int j = 0; j < 6; j++) {
				if (matches[j] == 2) {
					finalValue[8] = 25; // Full House
				}
			}
			finalValue[6] = diceNum[0] + diceNum[1] + diceNum[2] + diceNum[3] + diceNum[4]; // 3 of a kind
		} else if (matches[i] == 4) {
			finalValue[7] = diceNum[0] + diceNum[1] + diceNum[2] + diceNum[3] + diceNum[4]; // 4 of a kind
		} else if (matches[i] == 5) { // Yahtzee
			finalValue[11]++;
		}
		if (diceNum[i] == 1) { // Counts which numbers are present
			foundNums[0] = true;
		} else if (diceNum[i] == 2) {
			foundNums[1] = true;
		} else if (diceNum[i] == 3) {
			foundNums[2] = true;
		} else if (diceNum[i] == 4) {
			foundNums[3] = true;
		} else if (diceNum[i] == 5) {
			foundNums[4] = true;
		} else if (diceNum[i] == 6) {
			foundNums[5] = true;
		}
	}
	if (foundNums[0] + foundNums[1] + foundNums[2] + foundNums[3] + foundNums[4] + foundNums[5] >= 4) { // Small Straight
		finalValue[9] = 30;
	}
	if (foundNums[0] + foundNums[1] + foundNums[2] + foundNums[3] + foundNums[4] + foundNums[5] == 5) { // Large Straight
		finalValue[10] = 40;
	}

	finalValue[12] = diceNum[0] + diceNum[1] + diceNum[2] + diceNum[3] + diceNum[4]; // Chance
	
	if (save) {
		switch (selectedBox) {
		case 1:
			score->ONES[currentPlayer - 1] = finalValue[0];
			score->FILLED[currentPlayer - 1][0] = true;
			break;
		case 2:
			score->TWOS[currentPlayer - 1] = finalValue[1];
			score->FILLED[currentPlayer - 1][1] = true;
			break;
		case 3:
			score->THREES[currentPlayer - 1] = finalValue[2];
			score->FILLED[currentPlayer - 1][2] = true;
			break;
		case 4:
			score->FOURS[currentPlayer - 1] = finalValue[3];
			score->FILLED[currentPlayer - 1][3] = true;
			break;
		case 5:
			score->FIVES[currentPlayer - 1] = finalValue[4];
			score->FILLED[currentPlayer - 1][4] = true;
			break;
		case 6:
			score->SIXES[currentPlayer - 1] = finalValue[5];
			score->FILLED[currentPlayer - 1][5] = true;
			break;
		case 7:
			score->OFKIND_THREE[currentPlayer - 1] = finalValue[6];
			score->FILLED[currentPlayer - 1][6] = true;
			break;
		case 8:
			score->OFKIND_FOUR[currentPlayer - 1] = finalValue[7];
			score->FILLED[currentPlayer - 1][7] = true;
			break;
		case 9:
			score->FULL_HOUSE[currentPlayer - 1] = finalValue[8];
			score->FILLED[currentPlayer - 1][8] = true;
			break;
		case 10:
			score->STRAIGHT_SMALL[currentPlayer - 1] = finalValue[9];
			score->FILLED[currentPlayer - 1][9] = true;
			break;
		case 11:
			score->STRAIGHT_LARGE[currentPlayer - 1] = finalValue[10];
			score->FILLED[currentPlayer - 1][10] = true;
			break;
		case 12:
			score->YAHTZEE[currentPlayer - 1] = finalValue[11] * 50;
			score->FILLED[currentPlayer - 1][11] = true;
			break;
		case 13:
			score->CHANCE[currentPlayer - 1] = finalValue[12];
			score->FILLED[currentPlayer - 1][12] = true;
			break;
		}
	}

	// Upper Section
	for (int i = 0; i < 6; i++) {
		if (!score->FILLED[currentPlayer - 1][i]) {
			al_draw_textf(text16, black, 436, upper + 2, ALLEGRO_ALIGN_CENTER, "%d", finalValue[i]);
		} else {
			switch (i) {
			case 0:
				al_draw_textf(text16, gray, 436, upper + 2, ALLEGRO_ALIGN_CENTER, "%d", score->ONES[currentPlayer - 1]);
				break;
			case 1:
				al_draw_textf(text16, gray, 436, upper + 2, ALLEGRO_ALIGN_CENTER, "%d", score->TWOS[currentPlayer - 1]);
				break;
			case 2:
				al_draw_textf(text16, gray, 436, upper + 2, ALLEGRO_ALIGN_CENTER, "%d", score->THREES[currentPlayer - 1]);
				break;
			case 3:
				al_draw_textf(text16, gray, 436, upper + 2, ALLEGRO_ALIGN_CENTER, "%d", score->FOURS[currentPlayer - 1]);
				break;
			case 4:
				al_draw_textf(text16, gray, 436, upper + 2, ALLEGRO_ALIGN_CENTER, "%d", score->FIVES[currentPlayer - 1]);
				break;
			case 5:
				al_draw_textf(text16, gray, 436, upper + 2, ALLEGRO_ALIGN_CENTER, "%d", score->SIXES[currentPlayer - 1]);
				break;
			}
		}
		upper+=26;
	}
	upper = 388;

	// Lower Section
	for (int i = 6; i < 13; i++) {
		if (!score->FILLED[currentPlayer - 1][i]) {
			if (i == 11) {
				al_draw_textf(text16, black, 436, upper + 2, ALLEGRO_ALIGN_CENTER, "%d", finalValue[i] * 50);
			} else {
				al_draw_textf(text16, black, 436, upper + 2, ALLEGRO_ALIGN_CENTER, "%d", finalValue[i]);
			}
		} else {
			switch (i) {
			case 6:
				al_draw_textf(text16, gray, 436, upper + 2, ALLEGRO_ALIGN_CENTER, "%d", score->OFKIND_THREE[currentPlayer - 1]);
				break;
			case 7:
				al_draw_textf(text16, gray, 436, upper + 2, ALLEGRO_ALIGN_CENTER, "%d", score->OFKIND_FOUR[currentPlayer - 1]);
				break;
			case 8:
				al_draw_textf(text16, gray, 436, upper + 2, ALLEGRO_ALIGN_CENTER, "%d", score->FULL_HOUSE[currentPlayer - 1]);
				break;
			case 9:
				al_draw_textf(text16, gray, 436, upper + 2, ALLEGRO_ALIGN_CENTER, "%d", score->STRAIGHT_SMALL[currentPlayer - 1]);
				break;
			case 10:
				al_draw_textf(text16, gray, 436, upper + 2, ALLEGRO_ALIGN_CENTER, "%d", score->STRAIGHT_LARGE[currentPlayer - 1]);
				break;
			case 11:
				al_draw_textf(text16, gray, 436, upper + 2, ALLEGRO_ALIGN_CENTER, "%d", score->YAHTZEE[currentPlayer - 1] * 50);
				break;
			case 12:
				al_draw_textf(text16, gray, 436, upper + 2, ALLEGRO_ALIGN_CENTER, "%d", score->CHANCE[currentPlayer - 1]);
				break;
			}
		}
		upper += 26;
	}

	if (score->YAHTZEE[currentPlayer - 1] != 0) {
		upper = 413;
		for (int i = 0; i < score->YAHTZEE[currentPlayer - 1]; i++) {
			al_draw_filled_rectangle(upper, 569, upper + 16, 594, gray);
			upper += 17;
		}
		al_draw_textf(text16, gray, 436, 597, ALLEGRO_ALIGN_CENTER, "%d", score->YAHTZEE[currentPlayer - 1] * 50);
	}

	return finalValue[selectedBox - 1];
}

struct playerScore refreshScores (playerScore *score) {
	return *score;
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
	// Intializes random numbers
	srand(time(0));

	// Read in user settings
	uSettings options;         // Calls upon uSettings Struct
	options = prevSettings();  // Calls upon prevSettings function to read in current user settings

	al_set_new_display_refresh_rate(options.FPS);

	// Initialize Essential Allegro Elements
	ALLEGRO_DISPLAY *display = al_create_display(options.SCREEN_W, options.SCREEN_H);
	ALLEGRO_BITMAP *icon = al_load_bitmap("./assets/icon.png");
	ALLEGRO_TIMER *timer = al_create_timer(1 / options.FPS);
	ALLEGRO_TIMER *playButtonAppear = al_create_timer(3);
	ALLEGRO_TIMER *autoEndTurn = al_create_timer(2);
	ALLEGRO_TIMER *animTimer = al_create_timer(2.5);
	ALLEGRO_TIMER *yahtzeeTimer = al_create_timer(3);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_EVENT events;

	al_set_window_title(display, "Yahtzee V0.0.8");
	al_set_display_icon(display, icon);

	// Initialize Non-essential Allegro Elements
	ALLEGRO_VIDEO *titlescreen = al_open_video("./assets/Yahtzee0001-7198.ogv");
	ALLEGRO_VIDEO *playingBG = al_open_video("./assets/Playing Background.ogv");
	ALLEGRO_VIDEO *scoringVideo = al_open_video("./assets/Scorecard Screen.ogv");
	ALLEGRO_BITMAP *pause = al_load_bitmap("./assets/Paused Screen.png");
	ALLEGRO_BITMAP *gamemode = al_load_bitmap("./assets/Gamemode Screen.png");
	ALLEGRO_BITMAP *optionsScreen = al_load_bitmap("./assets/Options Screen.png");
	ALLEGRO_BITMAP *optionSlider = al_load_bitmap("./assets/Options Slider Button.png");
	ALLEGRO_BITMAP *playerAdd = al_load_bitmap("./assets/Players Screen.png");
	ALLEGRO_BITMAP *die = al_load_bitmap("./assets/Die.png");
	ALLEGRO_BITMAP *button = al_load_bitmap("./assets/Button.png");
	ALLEGRO_BITMAP *dieOverlay = al_load_bitmap("./assets/Die Overlay.png");
	ALLEGRO_BITMAP *boxOverlay = al_load_bitmap("./assets/Scorecard Highlight.png");
	ALLEGRO_BITMAP *yahtzeeLogo = al_load_bitmap("./assets/Logo.png");
	ALLEGRO_SAMPLE *error = al_load_sample("./assets/Error Sound Effect.mp3");
	ALLEGRO_SAMPLE_ID mus;
	ALLEGRO_SAMPLE_ID yahtz;
	ALLEGRO_SAMPLE *music = al_load_sample("./assets/Background Music.mp3");
	ALLEGRO_SAMPLE *celebration = al_load_sample("./assets/pixiedust.mp3");
	ALLEGRO_FONT *text72 = al_load_font("./assets/Montserrat-ExtraBold.ttf", 72, NULL);
	ALLEGRO_FONT *text54 = al_load_font("./assets/Montserrat-ExtraBold.ttf", 54, NULL);
	ALLEGRO_FONT *text36 = al_load_font("./assets/Montserrat-ExtraBold.ttf", 36, NULL);
	ALLEGRO_FONT *text24 = al_load_font("./assets/Montserrat-ExtraBold.ttf", 24, NULL);
	ALLEGRO_FONT *text16 = al_load_font("./assets/Montserrat-ExtraBold.ttf", 16, NULL);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR red = al_map_rgb(230, 60, 56);
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR gray = al_map_rgb(34, 47, 62);
	

	// Register Events Sources
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(playButtonAppear));
	al_register_event_source(event_queue, al_get_timer_event_source(autoEndTurn));
	al_register_event_source(event_queue, al_get_timer_event_source(animTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(yahtzeeTimer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_video_event_source(titlescreen));
	al_register_event_source(event_queue, al_get_video_event_source(playingBG));
	al_register_event_source(event_queue, al_get_video_event_source(scoringVideo));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	// Initialize Standard Variables
	bool exit = false, draw = true, showPlayButton = false, uno = false, sliderToggle[5] = {false, false, false, false, false}, 
	rolling[5] = {false, false, false, false, false}, rollAnim[5] = {false, false, false, false, false}, spin = true, rollSlow = false, saveScore = false, yahtzee = false, textAppear = false;
	int mouseX = 0, mouseY = 0, titleFade = 0, sliderX[5] = {(options.SCREEN_W - 1280) * 2.225, (options.SCREEN_H - 720) * 1.25, (options.FPS - 60) * 4, (options.SOUND_EFFECTS - 1) * 140, (options.MUSIC - 1) * 140}, 
		mouseOffsetX = 0, sliderMoved[5] = {(options.SCREEN_W - 1280) * 2.225, (options.SCREEN_H - 720) * 1.25, (options.FPS - 60) * 4, (options.SOUND_EFFECTS - 1) * 140, (options.MUSIC - 1) * 140 },
		players = 2, randColour = 0, colours[20][3] = {{29, 209, 161}, {72, 219, 251}, {255, 159, 67}, {52, 31, 151}, {243, 104, 224}, {200, 214, 229}, {95, 39, 205}, {238, 82, 83}}, currentPlayer = 1, diceNum[5] = {0, 0, 0, 0, 0}, 
		rollTimer = 0, dieOffset = 0, turn = 1, box = 0, boxSelected = 0, debug = 1, totals[6] = {0, 0, 0, 0, 0, 0};
	float sliderNum[5] = {options.SCREEN_W, options.SCREEN_H, options.FPS, options.SOUND_EFFECTS, options.MUSIC};

	playerScore score;

	screen = Title;

	// Begin Game Loop
	al_start_video(titlescreen, al_get_default_mixer());
	al_start_video(playingBG, al_get_default_mixer());
	al_start_video(scoringVideo, al_get_default_mixer());
	al_set_video_playing(scoringVideo, false);
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
			box = buttonCheck(display, mouseX, mouseY, showPlayButton, sliderX, currentPlayer, &score);
			if (screen == Options) {
				if (sliderToggle[0]) { // Screen W
					sliderX[0] = mouseX - mouseOffsetX + sliderMoved[0];
					if (sliderX[0] <= -115) {
						sliderX[0] = -115;
					} else if (sliderX[0] >= 110) {
						sliderX[0] = 110;
					} 
					sliderNum[0] = sliderX[0] * 2.225 + 1280;
					draw = true;
				} else if (sliderToggle[1]) { // Screen H
					sliderX[1] = mouseX - mouseOffsetX + sliderMoved[1];
					if (sliderX[1] <= -115) {
						sliderX[1] = -115;
					} else if (sliderX[1] >= 110) {
						sliderX[1] = 110;
					}
					sliderNum[1] = sliderX[1] * 1.25 + 720;
					draw = true;
				} else if (sliderToggle[2]) { // FPS
					sliderX[2] = mouseX - mouseOffsetX + sliderMoved[2];
					if (sliderX[2] <= -145) {
						sliderX[2] = -145;
					} else if (sliderX[2] >= 82) {
						sliderX[2] = 82;
					} 
					sliderNum[2] = (sliderX[2] * 0.245) + 60;
					draw = true;
				} else if (sliderToggle[3]) { // SOUND EFFCTS VOLUME
					sliderX[3] = mouseX - mouseOffsetX + sliderMoved[3];
					if (sliderX[3] <= -112) {
						sliderX[3] = -112;
					} else if (sliderX[3] >= 115) {
						sliderX[3] = 115;
					}
					sliderNum[3] = (sliderX[3] * 0.0085) + 1;
					draw = true;
				} else if (sliderToggle[4]) { // MUSIC VOLUME
					sliderX[4] = mouseX - mouseOffsetX + sliderMoved[4];
					if (sliderX[4] <= -112) {
						sliderX[4] = -112;
					} else if (sliderX[4] >= 115) {
						sliderX[4] = 115;
					}
					sliderNum[4] = (sliderX[4] * 0.0085) + 1;
					draw = true;
				}
			}
		}
		// Checks for mouse clicks
		if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (events.mouse.button & 1) {
				if (screen == Title && showPlayButton) {  // If buttons are met, and mouse is clicked, checks if mouse clicked the button, and acts accordingly
					if (mouseX >= options.SCREEN_W * 0.2 && mouseY >= options.SCREEN_H * 0.8 && mouseX <= options.SCREEN_W * 0.2 + 200 && mouseY <= options.SCREEN_H * 0.8 + 100) { // Title Play
						screen = GamePick;
						al_set_video_playing(titlescreen, false);
						al_set_video_playing(playingBG, true);
						al_play_sample(music, options.MUSIC, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, &mus);
						draw = true;
					} else if (mouseX >= options.SCREEN_W * 0.65 && mouseY >= options.SCREEN_H * 0.8 && mouseX <= options.SCREEN_W * 0.65 + 200 && mouseY <= options.SCREEN_H * 0.8 + 100) { // Title Quit
						exit = true;
					}
				} else if (screen == Paused) { // Pause screen buttons
					if (mouseX >= 50 && mouseX <= 205 && mouseY >= 150 && mouseY <= 205) { // Play
						screen = Playing;
						al_set_video_playing(playingBG, true);
						al_play_sample(music, options.MUSIC, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, &mus);
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
						al_play_sample(music, options.MUSIC, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, &mus);
						al_resume_timer(playButtonAppear);
						al_clear_to_color(black);
						draw = true;
					} else if (mouseX >= 50 && mouseX <= 580 && mouseY >= 450 && mouseY <= 505) { // Quit to desktop
						exit = true;
						break;
					}
				} else if (screen == GamePick) {
					if (mouseX >= 150 && mouseX <= 345 && mouseY >= 210 && mouseY <= 535) { // Local Multiplayer
						screen = gameSetup;
						al_seek_video(playingBG, 0);
						al_stop_sample(&mus);
						al_set_video_playing(playingBG, true);
						al_play_sample(music, options.MUSIC, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, &mus);
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
					if (mouseX >= sliderX[0] + 492 - 30 && mouseX <= sliderX[0] + 492 && mouseY >= 246 && mouseY <= 259) { // Slider 1
						sliderToggle[0] = true;
						mouseOffsetX = mouseX;
						al_hide_mouse_cursor(display);
					} else if (mouseX >= sliderX[1] + 492 - 30 && mouseX <= sliderX[1] + 492 && mouseY >= 276 && mouseY <= 289) { // Slider 2
						sliderToggle[1] = true;
						mouseOffsetX = mouseX;
						al_hide_mouse_cursor(display);
					} else if (mouseX >= sliderX[2] + 492 && mouseX <= sliderX[2] + 492 + 30 && mouseY >= 306 && mouseY <= 319) { // Slider 3
						sliderToggle[2] = true;
						mouseOffsetX = mouseX;
						al_hide_mouse_cursor(display);
					} else if (mouseX >= sliderX[3] + 492 - 30 && mouseX <= sliderX[3] + 492 && mouseY >= 336 && mouseY <= 349) { // Slider 4
						sliderToggle[3] = true;
						mouseOffsetX = mouseX;
						al_hide_mouse_cursor(display);
					} else if (mouseX >= sliderX[4] + 492 - 30 && mouseX <= sliderX[4] + 492 && mouseY >= 366 && mouseY <= 379) { // Slider 5
						sliderToggle[4] = true;
						mouseOffsetX = mouseX;
						al_hide_mouse_cursor(display);
					} else if (mouseX >= 944 && mouseX <= 1200 && mouseY >= 420 && mouseY <= 533) { // Save
						screen = GamePick;
						FILE *settings = fopen("UserSettings.txt", "w");
						fprintf(settings, "SCREEN_W = %.0f\nSCREEN_H = %.0f\nFPS = %.0f.0\nSOUND_EFFECTS = %.1f\nMUSIC = %.1f", sliderNum[0], sliderNum[1], sliderNum[2], sliderNum[3], sliderNum[4]);
						fclose(settings);
						if (options.FPS != sliderNum[2]) { // Changes Frame rate is chanegd by user
							options = prevSettings();
							al_set_timer_count(timer, 1 / options.FPS);
						}
						if (options.SCREEN_W != sliderNum[0] || options.SCREEN_H != sliderNum[1]) {
							options = prevSettings();
							al_resize_display(display, options.SCREEN_W, options.SCREEN_H);
						}
						if (options.MUSIC != sliderNum[4]) {
							options = prevSettings();
							al_stop_sample(&mus);
							al_play_sample(music, options.MUSIC, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, &mus);
						}
						draw = true;
					} else if (mouseX >= 747 && mouseX <= 913 && mouseY >= 603 && mouseY <= 676) { // Reset
						FILE *settings = fopen("UserSettings.txt", "w");
						fprintf(settings, "SCREEN_W = 1280\nSCREEN_H = 720\nFPS = 60.0\nSOUND_EFFECTS = 1.0\nMUSIC = 1.0");
						fclose(settings);
						for (int i = 0; i < 5; i++) 
							sliderX[i] = 0;
						mouseOffsetX = 0;
						al_resize_display(display, 1280, 720);
						al_stop_sample(&mus);
						if (options.FPS != sliderNum[2]) { 
							options = prevSettings();
							al_set_timer_count(timer, 1 / options.FPS);
						} else {
							options = prevSettings();
						}
						al_play_sample(music, options.MUSIC, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, &mus);
						sliderNum[0] = options.SCREEN_W, sliderNum[1] = options.SCREEN_H, sliderNum[2] = options.FPS, sliderNum[3] = options.SOUND_EFFECTS, sliderNum[4] = options.MUSIC;
						draw = true;
					} else if (mouseX >= 944 && mouseX <= 1200 && mouseY >= 560 && mouseY <= 676) { // Cancel
						screen = GamePick;
						draw = true;
					}
				} else if (screen == gameSetup) {
					if (mouseX >= 85 && mouseX <= 193 && mouseY >= 238 && mouseY <= 348) { // Subtract Players
						players--;
						if (players <= 1) {
							players = 2;
							al_play_sample(error, options.SOUND_EFFECTS, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						}
						draw = true;
					} else if (mouseX >= 1083 && mouseX <= 1194 && mouseY >= 238 && mouseY <= 348) { // Add Players
						players++;
						if (players >= 9) {
							players = 8;
							al_play_sample(error, options.SOUND_EFFECTS, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						}
						draw = true;
					} else if (mouseX >= 34 && mouseX <= 146 && mouseY >= 34 && mouseY <= 95) { // Go back
						screen = GamePick;
						draw = true;
					} else if (mouseX >= 975 && mouseX <= 1236 && mouseY >= 564 && mouseY <= 679) { // Play
						screen = Playing;
						draw = true;
					}
				} else if (screen == Playing) {
					if (mouseX >= options.SCREEN_W / 2 - 62.5 - 300 && mouseY >= options.SCREEN_H / 2 - 62.5 && mouseX <= options.SCREEN_W / 2 + 62.5 - 300 && mouseY <= options.SCREEN_H / 2 + 62.5) { // Die 1
						if (!rolling[0] && turn < 4) {
							rolling[0] = true;
							spin = true;
						} else if (rolling[0] && diceNum[0] != 0) { // Removes Spin button if none are selected
							rolling[0] = false;
							if (!rolling[1] && !rolling[2] && !rolling[3] && !rolling[4]) {
								spin = false;
							}
						}
					} else if (mouseX >= options.SCREEN_W / 2 - 62.5 - 150 && mouseY >= options.SCREEN_H / 2 - 62.5 && mouseX <= options.SCREEN_W / 2 + 62.5 - 150 && mouseY <= options.SCREEN_H / 2 + 62.5) { // Die 2
						if (!rolling[1] && turn < 4) {
							rolling[1] = true;
							spin = true;
						} else if (rolling[1] && diceNum[1] != 0) {
							rolling[1] = false;
							if (!rolling[0] && !rolling[2] && !rolling[3] && !rolling[4]) {
								spin = false;
							}
						}
					} else if (mouseX >= options.SCREEN_W / 2 - 62.5 && mouseY >= options.SCREEN_H / 2 - 62.5 && mouseX <= options.SCREEN_W / 2 + 62.5 && mouseY <= options.SCREEN_H / 2 + 62.5) { // Die 3
						if (!rolling[2] && turn < 4) {
							rolling[2] = true;
							spin = true;
						} else if (rolling[2] && diceNum[2] != 0) {
							rolling[2] = false;
							if (!rolling[0] && !rolling[1] && !rolling[3] && !rolling[4]) {
								spin = false;
							}
						}
					} else if (mouseX >= options.SCREEN_W / 2 - 62.5 + 150 && mouseY >= options.SCREEN_H / 2 - 62.5 && mouseX <= options.SCREEN_W / 2 + 62.5 + 150 && mouseY <= options.SCREEN_H / 2 + 62.5) { // Die 4
						if (!rolling[3] && turn < 4) {
							rolling[3] = true;
							spin = true;
						} else if (rolling[3] && diceNum[3] != 0) {
							rolling[3] = false;
							if (!rolling[0] && !rolling[1] && !rolling[2] && !rolling[4]) {
								spin = false;
							}
						}
					} else if (mouseX >= options.SCREEN_W / 2 - 62.5 + 300 && mouseY >= options.SCREEN_H / 2 - 62.5 && mouseX <= options.SCREEN_W / 2 + 62.5 + 300 && mouseY <= options.SCREEN_H / 2 + 62.5) { // Die 5
						if (!rolling[4] && turn < 4) {
							rolling[4] = true;
							spin = true;
						} else if (rolling[4] && diceNum[4] != 0) {
							rolling[4] = false;
							for (int i = 0; i < 5; i++) {
								if (!rolling[0] && !rolling[1] && !rolling[2] && !rolling[3]) {
									spin = false;
								}
							}
						}
					} else if (mouseX >= 994 && mouseY >= 580 && mouseX <= 1248 && mouseY <= 694) {
						if (spin) { // Spin
							for (int i = 0; i < 5; i++) {
								if (rolling[i]) {
									rollAnim[i] = true;
									rolling[i] = false;
								}
							}
							al_start_timer(animTimer);
						} else if (!rollAnim[0] && !rollAnim[1] && !rollAnim[2] && !rollAnim[3] && !rollAnim[4]) { // End Turn
							al_stop_timer(autoEndTurn);
							screen = Scoring;
							al_set_video_playing(playingBG, false);
							al_set_video_playing(scoringVideo, true);
							al_stop_sample(&mus);
							al_play_sample(music, options.MUSIC, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &mus);
							al_set_timer_speed(animTimer, 1.25);
							al_start_timer(animTimer);
							turn = 1;
						}
					}
				} else if (screen == Scoring) {
					if (textAppear) {
						switch (box) {
						case 1:
							if (!score.FILLED[currentPlayer - 1][0])
								boxSelected = 1;
							break;
						case 2:
							if (!score.FILLED[currentPlayer - 1][1])
								boxSelected = 2;
							break;
						case 3:
							if (!score.FILLED[currentPlayer - 1][2])
								boxSelected = 3;
							break;
						case 4:
							if (!score.FILLED[currentPlayer - 1][3])
								boxSelected = 4;
							break;
						case 5:
							if (!score.FILLED[currentPlayer - 1][4])
								boxSelected = 5;
							break;
						case 6:
							if (!score.FILLED[currentPlayer - 1][5])
								boxSelected = 6;
							break;
						case 7:
							if (!score.FILLED[currentPlayer - 1][6])
								boxSelected = 7;
							break;
						case 8:
							if (!score.FILLED[currentPlayer - 1][7])
								boxSelected = 8;
							break;
						case 9:
							if (!score.FILLED[currentPlayer - 1][8])
								boxSelected = 9;
							break;
						case 10:
							if (!score.FILLED[currentPlayer - 1][9])
								boxSelected = 10;
							break;
						case 11:
							if (!score.FILLED[currentPlayer - 1][10])
								boxSelected = 11;
							break;
						case 12:
							if (!score.FILLED[currentPlayer - 1][11])
								boxSelected = 12;
							break;
						case 13:
							if (!score.FILLED[currentPlayer - 1][12])
								boxSelected = 13;
							break;
						}
						if (mouseX >= 994 && mouseY >= 580 && mouseX <= 1248 && mouseY <= 694 && boxSelected != 0) { // End Turn
							saveScore = true;
							totals[5] = scoreCalculations(&score, diceNum[0], diceNum[1], diceNum[2], diceNum[3], diceNum[4], text16, black, gray, boxSelected, currentPlayer, saveScore);
							currentPlayer++;
							if (currentPlayer > players) {
								currentPlayer = 1;
							}
							for (int i = 0; i < 5; i++) {
								diceNum[i] = 0;
								rolling[i] = false;
							}
							screen = Playing;
							boxSelected = 0;
							spin = false;
							draw = true;
							saveScore = false;
							textAppear = false;
							al_set_video_playing(scoringVideo, false);
							al_set_video_playing(playingBG, true);
						}
					}
				}
			}
		} 

		if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			if (screen == Options) {
				if (sliderToggle[0]) {
					sliderToggle[0] = false;
					sliderMoved[0] = mouseX - 492;
					al_show_mouse_cursor(display);
				} else if (sliderToggle[1]) {
					sliderToggle[1] = false;
					sliderMoved[1] = mouseX - 492;
					al_show_mouse_cursor(display);
				} else if (sliderToggle[2]) {
					sliderToggle[2] = false;
					sliderMoved[2] = mouseX - 492;
					al_show_mouse_cursor(display);
				} else if (sliderToggle[3]) {
					sliderToggle[3] = false;
					sliderMoved[3] = mouseX - 492;
					al_show_mouse_cursor(display);
				} else if (sliderToggle[4]) {
					sliderToggle[4] = false;
					sliderMoved[4] = mouseX - 492;
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
					al_stop_sample(&mus);
					uno = true;
					draw = true;
				} else if (screen == Paused) {
					screen = Playing;
					al_set_video_playing(playingBG, true);
					al_play_sample(music, options.MUSIC, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, &mus);
					draw = true;
				} else if (screen == GamePick) {
					screen = Title;
					titleFade = 0;
					showPlayButton = false;
					al_set_video_playing(playingBG, false);
					al_stop_sample(&mus);
					al_seek_video(titlescreen, 0);
					al_set_video_playing(titlescreen, true);
					al_resume_timer(playButtonAppear);
					al_clear_to_color(black);
					draw = true;
				} else if (screen == GameOptions || screen == gameSetup || screen == Options) {
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
			} else if (screen == Scoring) {
				al_seek_video(scoringVideo, 0);
				al_set_video_playing(scoringVideo, true);
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
				} else {
					titleFade = 1;
				}
			} else if (screen == Playing || screen == GamePick || screen == Options || screen == gameSetup) {
				playVideo(display, playingBG);
			} else if (screen == Scoring) {
				playVideo(display, scoringVideo);
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
						al_draw_textf(text16, black, 245, 243, NULL, "%.0f", sliderNum[0]); 
						al_draw_scaled_bitmap(optionSlider, 0, 0, 1920, 1080, sliderX[0] - 30, -60, options.SCREEN_W, options.SCREEN_H, NULL); // Slider 1
						al_draw_textf(text16, black, 245, 274, NULL, "%.0f", sliderNum[1]);
						al_draw_scaled_bitmap(optionSlider, 0, 0, 1920, 1080, sliderX[1] - 30, -30, options.SCREEN_W, options.SCREEN_H, NULL); // Slider 2
						al_draw_textf(text16, black, 245, 305, NULL, "%.0f.0", sliderNum[2]);
						al_draw_scaled_bitmap(optionSlider, 0, 0, 1920, 1080, sliderX[2] - 3, 0, options.SCREEN_W, options.SCREEN_H, NULL); // Slider 3
						al_draw_textf(text16, black, 245, 335, NULL, "%.1f", sliderNum[3]);
						al_draw_scaled_bitmap(optionSlider, 0, 0, 1920, 1080, sliderX[3] - 35, 30, options.SCREEN_W, options.SCREEN_H, NULL); // Slider 4
						al_draw_textf(text16, black, 245, 365, NULL, "%.1f", sliderNum[4]);
						al_draw_scaled_bitmap(optionSlider, 0, 0, 1920, 1080, sliderX[4] - 35, 60, options.SCREEN_W, options.SCREEN_H, NULL); // Slider 5
					} else if (screen == gameSetup) {
						al_draw_scaled_bitmap(playerAdd, 0, 0, 1920, 1080, 0, 0, options.SCREEN_W, options.SCREEN_H, NULL);
						al_draw_textf(text72, white, options.SCREEN_W / 2, options.SCREEN_H / 2 - 115, ALLEGRO_ALIGN_CENTER, "%d Players", players);
					} else if (screen == Playing) { // Playing
						al_draw_textf(text72, white, options.SCREEN_W / 2, 24, ALLEGRO_ALIGN_CENTER, "Player %d", currentPlayer);
						al_draw_scaled_bitmap(die, 0, 0, 1080, 1080, options.SCREEN_W / 2 - 62.5 - 300, options.SCREEN_H / 2 - 62.5, options.SCREEN_W / 10.24, options.SCREEN_H / 5.76, NULL);
						al_draw_scaled_bitmap(die, 0, 0, 1080, 1080, options.SCREEN_W / 2 - 62.5 - 150, options.SCREEN_H / 2 - 62.5, options.SCREEN_W / 10.24, options.SCREEN_H / 5.76, NULL);
						al_draw_scaled_bitmap(die, 0, 0, 1080, 1080, options.SCREEN_W / 2 - 62.5 + 0, options.SCREEN_H / 2 - 62.5, options.SCREEN_W / 10.24, options.SCREEN_H / 5.76, NULL);
						al_draw_scaled_bitmap(die, 0, 0, 1080, 1080, options.SCREEN_W / 2 - 62.5 + 150, options.SCREEN_H / 2 - 62.5, options.SCREEN_W / 10.24, options.SCREEN_H / 5.76, NULL);
						al_draw_scaled_bitmap(die, 0, 0, 1080, 1080, options.SCREEN_W / 2 - 62.5 + 300, options.SCREEN_H / 2 - 62.5, options.SCREEN_W / 10.24, options.SCREEN_H / 5.76, NULL);
						if (rolling[0] || diceNum[0] == 0) {
							al_draw_scaled_bitmap(dieOverlay, 0, 0, 1188, 1188, options.SCREEN_W / 2 - 68.75 - 300, options.SCREEN_H / 2 - 68.75, options.SCREEN_W / 9.3, options.SCREEN_H / 5.24, NULL);
							rolling[0] = true;
							spin = true;
						}
						if (rolling[1] || diceNum[1] == 0) {
							al_draw_scaled_bitmap(dieOverlay, 0, 0, 1188, 1188, options.SCREEN_W / 2 - 68.75 - 150, options.SCREEN_H / 2 - 68.75, options.SCREEN_W / 9.3, options.SCREEN_H / 5.24, NULL);
							rolling[1] = true;
							spin = true;
						}
						if (rolling[2] || diceNum[2] == 0) {
							al_draw_scaled_bitmap(dieOverlay, 0, 0, 1188, 1188, options.SCREEN_W / 2 - 68.75, options.SCREEN_H / 2 - 68.75, options.SCREEN_W / 9.3, options.SCREEN_H / 5.24, NULL);
							rolling[2] = true;
							spin = true;
						}
						if (rolling[3] || diceNum[3] == 0) {
							al_draw_scaled_bitmap(dieOverlay, 0, 0, 1188, 1188, options.SCREEN_W / 2 - 68.75 + 150, options.SCREEN_H / 2 - 68.75, options.SCREEN_W / 9.3, options.SCREEN_H / 5.24, NULL);
							rolling[3] = true;
							spin = true;
						}
						if (rolling[4] || diceNum[4] == 0) {
							al_draw_scaled_bitmap(dieOverlay, 0, 0, 1188, 1188, options.SCREEN_W / 2 - 68.75 + 300, options.SCREEN_H / 2 - 68.75, options.SCREEN_W / 9.3, options.SCREEN_H / 5.24, NULL);
							rolling[4] = true;
							spin = true;
						}
						if (spin && turn < 4 && !rollAnim[0] && !rollAnim[1] && !rollAnim[2] && !rollAnim[3] && !rollAnim[4]) {
							al_draw_scaled_bitmap(button, 0, 0, 1920, 1080, 0, 0, options.SCREEN_W, options.SCREEN_H, NULL); // Button
							al_draw_text(text54, white, 1050, 605, NULL, "SPIN");
						} else if (!rollAnim[0] && !rollAnim[1] && !rollAnim[2] && !rollAnim[3] && !rollAnim[4]) {
							al_draw_scaled_bitmap(button, 0, 0, 1920, 1080, 0, 0, options.SCREEN_W, options.SCREEN_H, NULL); // Button
							al_draw_text(text36, white, 1020, 615, NULL, "END TURN");
						}
						for (int i = 0; i < 5; i++) { // Rolling Animation
							if (rollAnim[i]) {
								if (diceRoll(2, 1) == diceRoll(2, 1)) {
									diceNum[i] = diceRoll(6, 1);
									rollSlow = false;
								}
							}
						}

						al_draw_textf(text72, black, options.SCREEN_W / 2 - 300, options.SCREEN_H / 2 - 42, ALLEGRO_ALIGN_CENTER, "%d", diceNum[0]);
						al_draw_textf(text72, black, options.SCREEN_W / 2 - 150, options.SCREEN_H / 2 - 42, ALLEGRO_ALIGN_CENTER, "%d", diceNum[1]);
						al_draw_textf(text72, black, options.SCREEN_W / 2 - 0, options.SCREEN_H / 2 - 42, ALLEGRO_ALIGN_CENTER, "%d", diceNum[2]);
						al_draw_textf(text72, black, options.SCREEN_W / 2 + 150, options.SCREEN_H / 2 - 42, ALLEGRO_ALIGN_CENTER, "%d", diceNum[3]);
						al_draw_textf(text72, black, options.SCREEN_W / 2 + 300, options.SCREEN_H / 2 - 42, ALLEGRO_ALIGN_CENTER, "%d", diceNum[4]);

						if (yahtzee) {
							al_play_sample(celebration, options.SOUND_EFFECTS * 0.8, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, &yahtz);
							al_draw_scaled_bitmap(yahtzeeLogo, 0, 0, 1536, 583, options.SCREEN_W / 2 - 250, options.SCREEN_H / 2 - 150, (options.SCREEN_W / 1.25) / 2, (options.SCREEN_H / 1.8) / 2, NULL);
							titleFade *= 0.99;
							yahtzee = false;
						}
					} else if (screen == Scoring) {
						if (textAppear) {
							totals[5] = scoreCalculations(&score, diceNum[0], diceNum[1], diceNum[2], diceNum[3], diceNum[4], text16, black, gray, boxSelected, currentPlayer, saveScore);
							if (box != 0) {
								if (box <= 6) {
									al_draw_scaled_bitmap(boxOverlay, 0, 0, 1920, 1080, 0, box * 25 - 25 + (box - 1 * 1), options.SCREEN_W, options.SCREEN_H, NULL);
								} else if (box > 6) {
									al_draw_scaled_bitmap(boxOverlay, 0, 0, 1920, 1080, 0, box * 25 + 79 + (box - 1 * 1), options.SCREEN_W, options.SCREEN_H, NULL);
								}
							}

							score = refreshScores(&score);

							if (boxSelected != 0) {
								if (boxSelected <= 6) {
									al_draw_scaled_bitmap(boxOverlay, 0, 0, 1920, 1080, 0, boxSelected * 25 - 25 + (boxSelected - 1 * 1), options.SCREEN_W, options.SCREEN_H, NULL);
									totals[0] = score.ONES[currentPlayer - 1] + score.TWOS[currentPlayer - 1] + score.THREES[currentPlayer - 1] + score.FOURS[currentPlayer - 1] + score.FIVES[currentPlayer - 1] + score.SIXES[currentPlayer - 1] + totals[5];
									totals[3] = score.OFKIND_THREE[currentPlayer - 1] + score.OFKIND_FOUR[currentPlayer - 1] + score.FULL_HOUSE[currentPlayer - 1] + score.STRAIGHT_SMALL[currentPlayer - 1] + score.STRAIGHT_LARGE[currentPlayer - 1] + score.YAHTZEE[currentPlayer - 1] * 50 + score.CHANCE[currentPlayer - 1];
								} else if (boxSelected > 6) {
									al_draw_scaled_bitmap(boxOverlay, 0, 0, 1920, 1080, 0, boxSelected * 25 + 79 + (boxSelected - 1 * 1), options.SCREEN_W, options.SCREEN_H, NULL);
									totals[0] = score.ONES[currentPlayer - 1] + score.TWOS[currentPlayer - 1] + score.THREES[currentPlayer - 1] + score.FOURS[currentPlayer - 1] + score.FIVES[currentPlayer - 1] + score.SIXES[currentPlayer - 1];
									totals[3] = score.OFKIND_THREE[currentPlayer - 1] + score.OFKIND_FOUR[currentPlayer - 1] + score.FULL_HOUSE[currentPlayer - 1] + score.STRAIGHT_SMALL[currentPlayer - 1] + score.STRAIGHT_LARGE[currentPlayer - 1] + score.YAHTZEE[currentPlayer - 1] * 50 + score.CHANCE[currentPlayer - 1] + totals[5];
								} 
								al_draw_scaled_bitmap(button, 0, 0, 1920, 1080, 0, 0, options.SCREEN_W, options.SCREEN_H, NULL);
								al_draw_text(text36, white, 1020, 615, NULL, "END TURN");
							} else {
								totals[0] = score.ONES[currentPlayer - 1] + score.TWOS[currentPlayer - 1] + score.THREES[currentPlayer - 1] + score.FOURS[currentPlayer - 1] + score.FIVES[currentPlayer - 1] + score.SIXES[currentPlayer - 1];
								totals[3] = score.OFKIND_THREE[currentPlayer - 1] + score.OFKIND_FOUR[currentPlayer - 1] + score.FULL_HOUSE[currentPlayer - 1] + score.STRAIGHT_SMALL[currentPlayer - 1] + score.STRAIGHT_LARGE[currentPlayer - 1] + score.YAHTZEE[currentPlayer - 1] * 50 + score.CHANCE[currentPlayer - 1];
							}

							if (totals[0] >= 63) {
								totals[1] = 35;
							}
							totals[2] = totals[0] + totals[1];
							totals[4] = totals[2] + totals[3];
							al_draw_textf(text16, gray, 435, 284, ALLEGRO_ALIGN_CENTER, "%d", totals[0]);
							al_draw_textf(text16, gray, 435, 310, ALLEGRO_ALIGN_CENTER, "%d", totals[1]);
							al_draw_textf(text16, gray, 435, 336, ALLEGRO_ALIGN_CENTER, "%d", totals[2]);
							al_draw_textf(text16, gray, 435, 625, ALLEGRO_ALIGN_CENTER, "%d", totals[2]);
							al_draw_textf(text16, gray, 435, 651, ALLEGRO_ALIGN_CENTER, "%d", totals[3]);
							al_draw_textf(text16, gray, 435, 677, ALLEGRO_ALIGN_CENTER, "%d", totals[4]);
						}
					}
					draw = false;
					al_flip_display();
				}
			} else if (events.timer.source == playButtonAppear) {
			showPlayButton = true;
			al_stop_timer(playButtonAppear);
			} else if (events.timer.source == autoEndTurn) {
				for (int i = 0; i < 5; i++) {
					diceNum[i] = 0;
					rolling[i] = false;
				}
				currentPlayer++;
				if (currentPlayer > players) {
					currentPlayer = 1;
				}
				al_stop_timer(autoEndTurn);
				draw = true;
			} else if (events.timer.source == animTimer) {
				if (screen == Playing) {
					if (diceNum[0] == diceNum[1] && diceNum[1] == diceNum[2] && diceNum[2] == diceNum[3] && diceNum[3] == diceNum[4] && yahtzee == false) {
						yahtzee = true;
						titleFade = 1;
						al_start_timer(yahtzeeTimer);
					} else {
						yahtzee = false;
					}

					for (int i = 0; i < 5; i++) {
						rollAnim[i] = false;
						rolling[i] = false;
					}
					turn++;
					spin = false;
				} else if (screen == Scoring) {
					textAppear = true;
					draw = true;
					al_set_timer_speed(animTimer, 2.5);
				}
				al_stop_timer(animTimer);
				draw = true;
			} else if (events.timer.source == yahtzeeTimer) {
				yahtzee = false;
				al_stop_timer(yahtzeeTimer);
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