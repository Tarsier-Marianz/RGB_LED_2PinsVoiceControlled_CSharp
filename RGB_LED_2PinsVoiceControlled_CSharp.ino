int PWM_PIN             = 3;      // The output that drives the LED color

boolean stringComplete  = false;  // whether the string is complete
String cmd              = "";     // a string to hold incoming command
int rgbValue            = 0;
int voltages[7] {
  0,    // about zero volts
  51,   // about 1 volt
  102,  // about 2 volts
  128,  // about 2.5 volts
  153,  // about 3.0 volts
  204,  // about 4.0 volts
  255   // about 5.0 volts
};



void setup() {
  Serial.begin(9600);
  pinMode(PWM_PIN, OUTPUT);
}

void loop() {
  listenSerial();
  analogWrite(PWM_PIN, rgbValue);  
  delay(1);

}

void listenSerial() {
  if (stringComplete) {
    cmd.trim();
    if (cmd == "red" || cmd == "RED") {
      rgbValue = 102;
    } else  if (cmd == "green" || cmd == "GREEN") {
      rgbValue = 204;
    } else  if (cmd == "blue" || cmd == "BLUE") {
      rgbValue = 255;
    } else {
      rgbValue = 0;
    }
    // clear the string command:
    cmd = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();      // get new byte

    if (inChar == '\010') { //if enter key is BACKSPACE (DEC =8, HEX= 8, OCT= 010)
      cmd = cmd.substring(0, cmd.length() - 1);   //remove last char if backspace
    } else {
      // add it to the inputString:
      cmd += inChar;
    }
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\015') {  //if enter key is CARRIAGE RETURN (DEC =13, HEX= D, OCT= 015)
      stringComplete = true;
      Serial.println('\015');
    } else {
      Serial.write(inChar);
    }
  }
}

