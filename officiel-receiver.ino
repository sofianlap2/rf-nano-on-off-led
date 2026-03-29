#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10);
const byte address[6] = "NODE1";

const int ledPin = 4;

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);

  if (!radio.begin()) {
    Serial.println("Radio NOT detected!");
    while (1);
  }

  radio.setChannel(108);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);

  radio.openReadingPipe(0, address);
  radio.startListening();

  Serial.println("Receiver ready");
}

void loop() {
  if (radio.available()) {
    char text[32] = {0};

    radio.read(text, sizeof(text));

    Serial.print("Received: ");
    Serial.println(text);

    if (strcmp(text, "ON") == 0) {
      digitalWrite(ledPin, HIGH);
    } else if (strcmp(text, "OFF") == 0) {
      digitalWrite(ledPin, LOW);
    }
  }
}