#include IRremote.h

#define IRpin 14   
IRrecv receiver(IRpin);
const int relayPins[] = {21, 19, 16, 15};  

void setup() {
  Serial.begin(9600);
  receiver.enableIRIn(); 
  
   Set up relay pins
  for (int i = 0; i  4; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW);   Turn off relays initially
  }
}

void loop() {
   Checks received an IR signal
  if (receiver.decode()) {
    translator();
    receiver.resume();   Receive the next value
  }
}

void translator() {
   Takes command based on IR code received
  switch (receiver.decodedIRData.command) {
    case 90
      operateRelay(0);
      break;
    case 66
      operateRelay(1);
      break;
    case 74
      operateRelay(2);
      break;
    case 82
      operateRelay(3);
      break;
    default
      Serial.println(Button has no Function);
  }
}

void operateRelay(int relayIndex) {
   Toggle the relay
  digitalWrite(relayPins[relayIndex], !digitalRead(relayPins[relayIndex]));
  
   Print the status to serial
  Serial.print(Button Pressed - Relay Number );
  Serial.println(relayIndex + 1);
}
