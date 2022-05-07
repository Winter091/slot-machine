#ifndef _CONFIG_H_
#define _CONFIG_H_

namespace cfg {

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern const char* WINDOW_TITLE;

extern int SLOTSVIEW_X;
extern int SLOTSVIEW_Y;
extern int SLOTSVIEW_WIDTH;
extern int SLOTSVIEW_HEIGHT;

extern int START_BUTTON_X;
extern int START_BUTTON_Y;
extern int START_BUTTON_WIDTH;
extern int START_BUTTON_HEIGHT;

extern int STOP_BUTTON_X;
extern int STOP_BUTTON_Y;
extern int STOP_BUTTON_WIDTH;
extern int STOP_BUTTON_HEIGHT;

extern int NUM_SLOT_ROWS;
extern int NUM_SLOTS_IN_ROW;

extern int START_SPIN_DURATION_MS;
extern int SPIN_MAX_DURATION_MS;
extern int STOP_MIN_DURATION_MS;
extern int SHOW_RESULTS_DURATION_MS;

extern float MIN_ROW_SPEED;
extern float MAX_ROW_SPEED;

extern const char* WIN_MESSAGE;
extern const char* LOSE_MESSAGE;
}

#endif