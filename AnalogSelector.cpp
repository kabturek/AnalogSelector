
#include "Arduino.h"
#include "Adafruit_MCP23008.h"
#include "AnalogSelector.h"

namespace selector{
    AnalogSelector::AnalogSelector(){
      //take the saved values
      selected_input = 0;
      is_muted = false;
    }
    void AnalogSelector::setup(){
      // CANT do this in an initializer as the arduino wont boot :/ ?
      // selector
      selector1.begin(0);      // use address 0
      selector2.begin(1);      // use address 1
      // set all pins as outputs
      selector1.pins(B00000000);
      selector2.pins(B00000000);
      mute_all();
    }
    void AnalogSelector::toggle_mute(){
      set_input_to(selected_input, !is_muted);
    }
    void AnalogSelector::mute_all(){
      selector1.send(B10101010);
      selector1.send(B00000000);
      selector2.send(B10101010);
      selector2.send(B00000000);
    }
    uint8_t AnalogSelector::actual_input(){
      return selected_input;
    }
    void AnalogSelector::select(uint8_t input){
      // mute the actual input
      set_input_to(selected_input, false);
      //save the new input
      selected_input = input;
      // turn on the actual input
      set_input_to(selected_input, true);
    }
    Adafruit_MCP23008& AnalogSelector::selector_for(uint8_t input){
      if(input < 4){
        return selector1;
      } else {
        input -=4;
        return selector2;
      }
    }
    void AnalogSelector::set_input_to(uint8_t input, bool state){
      // choose the selector for that input number
      int mcp_output = input % 4;
      // choose the relay
      mcp_output = mcp_output << 1;
      // choose contact 0 - off, 1 - on
      if(state){
        mcp_output += 1;
      }
      //flip the bistable relay
      selector_for(input).digitalWrite(mcp_output, HIGH);
      selector_for(input).digitalWrite(mcp_output, LOW);
    }
}
