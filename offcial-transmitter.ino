#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10);
const byte address[6] = "NODE1";

const int buttonPin = 4;

void setup() {
  Serial.begin(115200);

  pinMode(buttonPin, INPUT_PULLUP); // button to GND

  if (!radio.begin()) {
    Serial.println("Radio NOT detected!");
    while (1);
  }

  radio.setChannel(108);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);

  radio.openWritingPipe(address);
  radio.stopListening();

  Serial.println("Transmitter ready");
}

void loop() {
  bool buttonState = digitalRead(buttonPin);

  const char* message;

  if (buttonState == LOW) {
    message = "ON";   // pressed
  } else {
    message = "OFF";  // released
  }

  radio.write(message, strlen(message) + 1);

  Serial.println(message);

  delay(100); // faster response
}