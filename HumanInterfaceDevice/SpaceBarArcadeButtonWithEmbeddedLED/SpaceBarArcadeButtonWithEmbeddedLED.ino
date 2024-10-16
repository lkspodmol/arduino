
/**
 * Basic arcade button as a space bar example. Press arcade button, sends a SPACE BAR
 * via Arduino keyboard emulation.
 *
 * See also: SpaceBarArcadeButtonWithEmbeddedLEDFade.ino
 *
 * Should work with any button with an embedded LED, such as:
 * - Arcade Button with LED - 30mm: https://www.adafruit.com/product/3489
 * - Triangle Arcade buttons: https://www.adafruit.com/product/4190
 * - 16mm illuminated buttons: https://www.adafruit.com/product/1439
 *
 * Tutorials here: https://makeabilitylab.github.io/physcomp
 *   
 * By Jon E. Froehlich
 * @jonfroehlich
 * http://makeabilitylab.io
 *
 */

 #include <Keyboard.h> // https://www.arduino.cc/reference/en/language/functions/usb/keyboard/

const int ARCADE_BUTTON_INPUT_PIN = 2;
const int ARCADE_BUTTON_LED_PIN = 3; // needs to be a PWM pin
const int MAX_FADE_VAL = 100; // should be less than max PWM output
bool _btnPressed = false;

void setup() {
  Serial.begin(9600); // for debugging
  Keyboard.begin();
  pinMode(ARCADE_BUTTON_INPUT_PIN, INPUT_PULLUP);
  pinMode(ARCADE_BUTTON_LED_PIN, OUTPUT);
}

void loop() {
  int btnVal = digitalRead(ARCADE_BUTTON_INPUT_PIN);
  if(btnVal == LOW){ // internal-pull configuration
    digitalWrite(ARCADE_BUTTON_LED_PIN, HIGH); // turn on embedded LED
    _btnPressed = true;
    Keyboard.press(' ');
    Serial.println("Spacebar PRESSED!");
  }else{
    if(_btnPressed){
      _btnPressed = false;
      digitalWrite(ARCADE_BUTTON_LED_PIN, LOW); // turn on embedded LED
      Keyboard.release(' ');
      Serial.println("Spacebar RELEASED!");
    }
  }

  delay(20); // Slight delay, sampling at 50 Hz
}
