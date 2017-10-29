int ledPin = D3;
int maxHum = 70;
int minTemp = 290;
int loopCount = 0;
int currHum = 95;
int currTemp = 260;
char* rain = NULL;

void setup() {
  Serial.begin(9600);
  Particle.subscribe("hook-response/weather", gotWeather, MY_DEVICES);
  Particle.variable("humidity", &maxHum, INT);
  Particle.variable("temperature", &minTemp, INT);
  Particle.variable("c_hum", &currHum, INT);
  Particle.variable("c_temp", &currTemp, INT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (loopCount == 120000) {
    Serial.println("Requesting weather");

    Particle.publish("weather");
    loopCount = 0;
  }

  int anRead0 = analogRead(A0);
  maxHum = map(anRead0, 0, 4095, 0, 100);
  int anRead1 = analogRead(A1);
  minTemp = map(anRead1, 0, 4095, 255, 339);

  if (rain == NULL && currHum < maxHum && currTemp > minTemp) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  loopCount++;
  Particle.process();
}

void gotWeather(const char* name, const char* data) {
  String str = String(data);

  // find location of humidity, temperature, and rain
  int humIndex = str.indexOf("humidity");
  int tempIndex = str.indexOf("temp");
  rain = strstr(data, "rain");

  currHum = atoi(str.substring(humIndex + 10, humIndex + 12));
  currTemp = atoi(str.substring(tempIndex + 6, tempIndex + 9));
}
