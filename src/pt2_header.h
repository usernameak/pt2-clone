#pragma once

#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#ifdef _WIN32
#define WIN32_MEAN_AND_LEAN
#include <windows.h> // MAX_PATH
#else
#include <limits.h> // PATH_MAX
#endif
#include <stdint.h>
#include "pt2_unicode.h"
#include "pt2_palette.h"

#define PROG_VER_STR "1.35"

#ifdef _WIN32
#define DIR_DELIMITER '\\'
#define PATH_MAX MAX_PATH
#else
#define DIR_DELIMITER '/'
#define _stricmp strcasecmp
#define _strnicmp strncasecmp
#endif

#define SAMPLE_VIEW_HEIGHT 64
#define SAMPLE_AREA_WIDTH 314

#define SCREEN_W 320
#define SCREEN_H 255

/* "60Hz" ranges everywhere from 59..61Hz depending on the monitor, so with
** no vsync we will get stuttering because the rate is not perfect...
*/
#define VBLANK_HZ 60

/* Scopes are clocked at 64Hz instead of 60Hz to prevent the small +/- Hz 
** interference from monitors not being exactly 60Hz (and unstable non-vsync mode).
** Sadly, the scopes might midly flicker from this in some cases.
*/
#define SCOPE_HZ 64

#define FONT_CHAR_W 8 // actual data length is 7, includes right spacing (1px column)
#define FONT_CHAR_H 5

#define MOD_ROWS 64
#define MOD_SAMPLES 31
#define MOD_ORDERS 128
#define MAX_PATTERNS 100

#define MAX_SAMPLE_LEN 65534

// for NULL pointers
#define RESERVED_SAMPLE_OFFSET ((31+1) * MAX_SAMPLE_LEN)

#define AMIGA_VOICES 4
#define SCOPE_WIDTH 40
#define SCOPE_HEIGHT 33
#define SPECTRUM_BAR_NUM 23
#define SPECTRUM_BAR_HEIGHT 36
#define SPECTRUM_BAR_WIDTH 6

#define POSED_LIST_SIZE 12

// main crystal oscillator for PAL Amiga systems
#define AMIGA_PAL_XTAL_HZ 28375160

#define AMIGA_PAL_CCK_HZ (AMIGA_PAL_XTAL_HZ/8.0)

// nominal framerate in normal PAL videomodes (~49.92Hz)
#define AMIGA_PAL_VBLANK_HZ (AMIGA_PAL_CCK_HZ / (double)(313*227))

#define PAULA_PAL_CLK AMIGA_PAL_CCK_HZ
#define CIA_PAL_CLK (AMIGA_PAL_CCK_HZ / 5.0)

#define PAL_PAULA_MIN_SAFE_PERIOD 124
#define PAL_PAULA_MAX_SAFE_HZ (PAULA_PAL_CLK / (double)PAL_PAULA_MIN_SAFE_PERIOD)

#define FILTERS_BASE_FREQ (PAULA_PAL_CLK / 214.0)

#define KEYB_REPEAT_DELAY 17

// .MOD types
enum
{
	FORMAT_MK, // ProTracker or compatible
	FORMAT_FLT, // Startrekker (4 channels)
	FORMAT_FT2, // FT2 (or other trackers, multichannel)
	FORMAT_STK, // The Ultimate SoundTracker (15 samples)
	FORMAT_NT, // NoiseTracker
	FORMAT_HMNT, // His Master's NoiseTracker (special one)

	FORMAT_UNKNOWN // may be The Ultimate Soundtracker (set to FORMAT_STK later)
};

enum
{
	FLAG_NOTE = 1,
	FLAG_SAMPLE = 2,
	FLAG_NEWSAMPLE = 4,

	TEMPFLAG_START = 1,
	TEMPFLAG_DELAY = 2,

	FILTERMODEL_A1200 = 0,
	FILTERMODEL_A500 = 1,
	FILTER_LED_ENABLED = 2,

	NO_CARRY = 0,
	DO_CARRY = 1,

	INCREMENT_SLOW = 0,
	INCREMENT_FAST = 1,

	NO_SAMPLE_CUT = 0,
	SAMPLE_CUT = 1,

	EDIT_SPECIAL = 0,
	EDIT_NORMAL = 1,

	EDIT_TEXT_NO_UPDATE = 0,
	EDIT_TEXT_UPDATE = 1,

	TRANSPOSE_ALL = 1,

	MOUSE_BUTTON_NOT_HELD = 0,
	MOUSE_BUTTON_HELD = 1,

	DONT_SET_ORDER = -1,
	DONT_SET_PATTERN = -1,
	DONT_SET_ROW = -1,

	REMOVE_SAMPLE_MARKING = 0,
	KEEP_SAMPLE_MARKING  = 1,

	MOD_NOT_MODIFIED = 0,
	MOD_IS_MODIFIED = 1,

	DONT_CHECK_IF_FILE_EXIST = 0,
	CHECK_IF_FILE_EXIST = 1,

	DONT_GIVE_NEW_FILENAME = 0,
	GIVE_NEW_FILENAME = 1,

	DONT_DOWNSAMPLE = 0,
	DO_DOWNSAMPLE = 1,

	SCREEN_ALL = 0,
	SCREEN_MAINSCREEN = 1,
	SCREEN_DISKOP = 2,
	SCREEN_SAMPLER = 4,
	SCREEN_QUIT = 8,
	SCREEN_CLEAR = 16,

	VISUAL_QUADRASCOPE = 0,
	VISUAL_SPECTRUM = 1,

	MODE_IDLE = 0,
	MODE_EDIT = 1,
	MODE_PLAY = 2,
	MODE_RECORD = 3,

	RECORD_PATT = 0,
	RECORD_SONG = 1,

	CURSOR_NOTE = 0,
	CURSOR_SAMPLE1 = 1,
	CURSOR_SAMPLE2 = 2,
	CURSOR_CMD = 3,
	CURSOR_PARAM1 = 4,
	CURSOR_PARAM2 = 5,

	PLAY_MODE_NORMAL = 0,
	PLAY_MODE_PATTERN = 1,

	OCTAVE_HIGH = 0,
	OCTAVE_LOW = 1,

	DISKOP_MODE_MOD = 0,
	DISKOP_MODE_SMP = 1,

	DISKOP_SMP_WAV = 0,
	DISKOP_SMP_IFF = 1,
	DISKOP_SMP_RAW = 2,

	ASK_QUIT = 0,
	ASK_SAVE_MODULE = 1,
	ASK_SAVE_SONG = 2,
	ASK_SAVE_SAMPLE = 3,
	ASK_MOD2WAV = 4,
	ASK_MOD2WAV_OVERWRITE = 5,
	ASK_SAVEMOD_OVERWRITE = 6,
	ASK_SAVESMP_OVERWRITE = 7,
	ASK_LOAD_DOWNSAMPLE = 8,
	ASK_RESAMPLE = 9,
	ASK_KILL_SAMPLE = 10,
	ASK_UPSAMPLE = 11,
	ASK_DOWNSAMPLE = 12,
	ASK_FILTER_ALL_SAMPLES = 13,
	ASK_BOOST_ALL_SAMPLES = 14,
	ASK_MAKE_CHORD = 15,
	ASK_SAVE_ALL_SAMPLES = 16,
	ASK_PAT2SMP = 17,
	ASK_RESTORE_SAMPLE = 18,
	ASK_DISCARD_SONG = 19,
	ASK_DISCARD_SONG_DRAGNDROP = 20,

	TEMPO_MODE_CIA = 0,
	TEMPO_MODE_VBLANK = 1,

	TEXT_EDIT_STRING = 0,
	TEXT_EDIT_DECIMAL = 1,
	TEXT_EDIT_HEX = 2
};

int8_t *allocMemForAllSamples(void); // pt2_replayer.c

void restartSong(void);
void resetSong(void);
void incPatt(void);
void decPatt(void);
void modSetPos(int16_t order, int16_t row);
void modStop(void);
void doStopIt(bool resetPlayMode);
void playPattern(int8_t startRow);
void modPlay(int16_t patt, int16_t order, int8_t row);
void modSetSpeed(int32_t speed);
void modSetTempo(int32_t bpm, bool doLockAudio);
void modFree(void);
bool setupAudio(void);
void audioClose(void);
void clearSong(void);
void clearSamples(void);
void clearAll(void);
void modSetPattern(uint8_t pattern);
