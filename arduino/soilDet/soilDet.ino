#include "SoilMoistureModel.h"
#include "DHT.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define DHTPIN 2
#define DHTTYPE DHT22   // or DHT11
DHT dht(DHTPIN, DHTTYPE);

#define ONE_WIRE_BUS 3  // DS18B20 soil temp sensor pin
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int relayPin = 9;
int ledPin = 7;
int buzzerPin = 8;

Eloquent::ML::Port::RandomForest clf;

float calcDewPoint(float tempC, float humidity) {
  double a = 17.27;
  double b = 237.7;
  double alpha = ((a * tempC) / (b + tempC)) + log(humidity / 100.0);
  return (b * alpha) / (a - alpha);
}

void setup() {
  Serial.begin(9600);

  dht.begin();
  sensors.begin();

  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(relayPin, LOW);
}

void loop() {
  float humidity = dht.readHumidity();
  float airTemp = dht.readTemperature();
  sensors.requestTemperatures();
  float soilTemp = sensors.getTempCByIndex(0);
  float dewPoint = calcDewPoint(airTemp, humidity);

  if (isnan(humidity) || isnan(airTemp) || soilTemp == DEVICE_DISCONNECTED_C) {
    Serial.println("Sensor error!");
    delay(2000);
    return;
  }

  float input[4] = { humidity, airTemp, soilTemp, dewPoint };
  String condition = clf.predictLabel(input);

  Serial.print("Humidity: "); Serial.println(humidity);
  Serial.print("Air Temp: "); Serial.println(airTemp);
  Serial.print("Soil Temp: "); Serial.println(soilTemp);
  Serial.print("Dew Point: "); Serial.println(dewPoint);
  Serial.print("Predicted Soil Condition: ");
  Serial.println(condition);

  if (condition == "Dry") {
    digitalWrite(relayPin, HIGH);
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    Serial.println("Soil is DRY -> Pump ON");
  }
  else {
    digitalWrite(relayPin, LOW);
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
    Serial.println("Soil is Optimal/Wet -> Pump OFF");
  }

  delay(5000);
}