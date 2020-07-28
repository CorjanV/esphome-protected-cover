#include "esphome.h"

using namespace std;

unsigned long last_time = 0;
unsigned long current_time = 0;

int exact_pos = 0;
int relative_pos = 0;

class CoverWithWindow : public Component, public Cover {
 public:
  int PIN_UP;
  int PIN_DOWN;
  int PIN_WINDOW;
  int UP_DURATION;
  int DOWN_DURATION;

  void setup() override {
    pinMode(PIN_UP, OUTPUT);
    pinMode(PIN_DOWN, OUTPUT);
    pinMode(PIN_WINDOW, INPUT_PULLUP);

    digitalWrite(PIN_UP, LOW);
    digitalWrite(PIN_DOWN, LOW);
  }
  CoverTraits get_traits() override {
    auto traits = CoverTraits();
    traits.set_is_assumed_state(true);
    traits.set_supports_position(true);
    traits.set_supports_tilt(false);
    return traits;
  }
  void control(const CoverCall &call) override {
    // This will be called every time the user requests a state change.
    if (call.get_position().has_value()) {
      if(!digitalRead(PIN_WINDOW))
      {
        int new_pos = *call.get_position()*100;
        relative_pos = exact_pos - new_pos;
        last_time = millis();
      } else {
        double current_position = this->position;
        this->position = *call.get_position();
        this->publish_state();
        delay(100);
        this->position = current_position;
        this->publish_state();
      }
    }
    if (call.get_stop()) {
      relative_pos = 0;
      digitalWrite(PIN_DOWN, LOW);
      digitalWrite(PIN_UP, LOW);
      this->position = exact_pos/100.0;
      this->publish_state();
    }
  }
  void loop() override {
    current_time = millis();

    if(relative_pos > 0) {
      digitalWrite(PIN_DOWN, LOW);
      digitalWrite(PIN_UP, HIGH);
      if(current_time - last_time >= (UP_DURATION / 100)) {
        last_time = current_time;
        relative_pos--;
        exact_pos--;
        if(exact_pos % 5 == 0) {
          this->position = exact_pos/100.0;
          this->publish_state();
        }
      }
      if(relative_pos == 0) {
        digitalWrite(PIN_DOWN, LOW);
        digitalWrite(PIN_UP, LOW);
        this->position = exact_pos/100.0;
        this->publish_state();
      }
    } 
    else if(relative_pos < 0) {
      digitalWrite(PIN_UP, LOW);
      digitalWrite(PIN_DOWN, HIGH);
      if(current_time - last_time >= (DOWN_DURATION / 100)) {
        last_time = current_time;
        relative_pos++;
        exact_pos++;
        if(exact_pos % 5 == 0) {
          this->position = exact_pos/100.0;
          this->publish_state();
        }
      }
      if(relative_pos == 0) {
        digitalWrite(PIN_DOWN, LOW);
        digitalWrite(PIN_UP, LOW);
        this->position = exact_pos/100.0;
        this->publish_state();
      }
    }
  }
};