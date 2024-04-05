#include <stdio.h>
#include <string>
#include <map>
//#include <stdlib.h>
#include "pico/stdlib.h"

#include "../presenter.hpp"

void initPin(uint32_t pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
#if PIN_USE_PULLUP
    gpio_pull_up(pin);
#endif

}

int main() {
//    stdio_init_all();

    std::map<uint32_t, uint64_t> pinSwitchTime;
    std::map<uint32_t, uint8_t> pinState;
    std::map<uint32_t, uint64_t> pinLastRepeatTime;
    
    PresenterMode mode = SINGLE_KEYDOWN;


    // Init all pins from pin2key and pin2key_scnd
    for (auto& pinMap : {pin2key, pin2key_scnd}) {
        for (auto& pair : pin2key) {
            uint32_t pin = pair.first; 
            if (pinSwitchTime.contains(pin))
                continue;
            initPin(pin);
            pinSwitchTime[pin] = 0;
            pinLastRepeatTime[pin] = 0;
            pinState[pin] = gpio_get(pin);
        }
    }


    while(true){
        // use pin2key_scnd when mode is repeated
        auto& pin2keyMap = (mode == SINGLE_KEYDOWN) ? pin2key : pin2key_scnd; 
        for (auto& pair : pin2keyMap) {
            uint32_t pin = pair.first;
            // Skip if debounce time is not over yet
            if (board_millis() - pinSwitchTime[pin] <= DEBOUNCE_DELAY_MS)
                continue; 
            let oldState = pinState[pin];
            let currentState = gpio_get(pin);
            if (currentState != oldState) {
                if (currentState == PIN_ACTIVE_VAL) {
                    // TODO simulate key down for pair.second

                } else {
                    // TODO simulate key up for pair.second
                    //TODO only if key up has not already been simulated due to pinSwitchTime
                    // E.g. keep key state in another map to avoid consecutive keyups/downs

                }
                pinSwitchTime[pin] = board_millis();
                pinState[pin] = currentState;

            }
            if (mode == REPEATED_KEYDOWN) {
                if (currentState == PIN_ACTIVE_VAL && 
                    board_millis() - pinSwitchTime[pin] > REPEAT_KEYDOWN_AFTER_MS &&
                    board_millis() - pinLastRepeatTime[pin] > REPEAT_KEYDOWN_PERIOD_MS )
                        // TODO simulate key down, then key up for pair.second
                        pinLastRepeatTime[pin] =  board_millis();
                }
            } else {
                if (currentState == PIN_ACTIVE_VAL && 
                    board_millis() - pinSwitchTime[pin] > KEYDOWN_LIFT_AFTER_MS) {
                        // TODO simulate key up for pair.second
                }
            }
        }
        sleep_ms(100);
    }

    return 0;
}