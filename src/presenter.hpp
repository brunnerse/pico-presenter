#pragma once

#include <map>
#include <cstdint>

#define PIN_ACTIVE_VAL 1
#define PIN_USE_PULLUP 0

// Map pins to keys
std::map<uint32_t, char> pin2key ({15: 'A'}, {16: 'B'}); 
std::map<uint32_t, char> pin2key_scnd ({15: 'x'}, {16: 'y'}); 

// Mode switch; Map pins to new keys (e.g. scroll), not once but continuous press

#define PIN_MODE_SWITCH 5

enum class PresenterMode {
    SINGLE_KEYDOWN,
    REPEATED_KEYDOWN
}

#define DEBOUNCE_DELAY_MS 5
#define REPEAT_KEYDOWN_AFTER_MS 500
#define REPEAT_KEYDOWN_PERIOD_MS 200

#define KEYDOWN_LIFT_AFTER_MS 50

