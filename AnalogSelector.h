#ifndef ANALOG_SELECTOR_H
#define ANALOG_SELECTOR_H
#include <Adafruit_MCP23008.h>

namespace arduino{
  namespace libraries{
    class AnalogSelector {
      public:
        AnalogSelector();
        void setup();
        uint8_t actual_input();
        void select(uint8_t input);
        void mute_all();
        void toggle_mute();
        uint8_t selected_input;
        Adafruit_MCP23008& selector_for(uint8_t input);
        Adafruit_MCP23008 selector1;
        Adafruit_MCP23008 selector2;
      private:
        void set_input_to(uint8_t input, bool state);
        bool is_muted;
    };
  }
}
#endif
