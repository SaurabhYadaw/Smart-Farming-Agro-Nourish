// Include the necessary libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Servo.h>

// Initialize the LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);  // 0x27 is the I2C address for the display

// Define the pins for the tactile switches
#define TACTILE_SWITCH_1_PIN 7
#define TACTILE_SWITCH_2_PIN 8
#define SERVO_PIN 9

// Define the pins for the sensors
#define DHT11_PIN 2
#define MOISTURE_SENSOR_PIN A0

// Initialize the DHT sensor
DHT dht(DHT11_PIN, DHT11);

Servo servoMotor;

bool takeReadings = true;
float humidity, temperature;
int moisture;
String predictedCrop = "";

void setup() {
  // Initialize the LCD
  lcd.init();
  lcd.backlight();

  // Initialize the DHT sensor
  dht.begin();
  servoMotor.attach(SERVO_PIN);
  servoMotor.write(0);

  // Set up the tactile switches as inputs with pull-up resistors
  pinMode(TACTILE_SWITCH_1_PIN, INPUT_PULLUP);
  pinMode(TACTILE_SWITCH_2_PIN, INPUT_PULLUP);

  // LCD display configuration..
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("AGRO NOURISH");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0);
  String message1 = "Feeding the";
  for (int i = 0; i < message1.length(); i++) {
    lcd.print(message1[i]);
    delay(300);
  }
  lcd.setCursor(0, 1);
  String message2 = "World Naturally!!";
  for (int i = 0; i < message2.length(); i++) {
    lcd.print(message2[i]);
    delay(300);
  }
  delay(8000);
}

void loop() {
  // Continuously take sensor readings
  if (takeReadings) {
    humidity = dht.readHumidity();  // Humidity is already in percentage
    temperature = dht.readTemperature();
    moisture = analogRead(MOISTURE_SENSOR_PIN);
    moisture = 100 - ((moisture / 1023.0) * 100);  // Convert moisture reading to percentage
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(humidity);
    lcd.print("%");  // Display humidity as percentage
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Moisture: ");
    lcd.print(moisture);
    lcd.print("%");  // Display moisture as percentage
    delay(2000);
  }

  // Check if button 1 is pressed
  if (digitalRead(TACTILE_SWITCH_1_PIN) == LOW) {
    predictedCrop = predictCropSuitability(temperature, humidity, moisture);

    if (predictedCrop.length() > 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Predicted Crop: ");
      lcd.setCursor(0, 1);
      lcd.print(predictedCrop);
      delay(5000);
      predictCropCultivationCycle(predictedCrop);
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("No Crop For");
      lcd.setCursor(0, 1);
      lcd.print("Cultivation !!");
      delay(5000);
    }
  }

  // Check if button 2 is pressed
  if (digitalRead(TACTILE_SWITCH_2_PIN) == LOW) {
    if (predictedCrop.length() > 0) {
      Serial.print(predictedCrop.length());
      predictCropCultivationCycle(predictedCrop);
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("No Crop For");
      lcd.setCursor(0, 1);
      lcd.print("Cultivation !!");
      delay(5000);
    }
  }
}
String predictCropSuitability(float temperature, float humidity, int moisture) {

  if ((temperature >= 15 && temperature <= 27) && (humidity >= 13 && humidity <= 14) && (moisture >= 21 && moisture <= 40)) {
    return "Rice and Wheat";
  } else if ((temperature >= 12 && temperature <= 25) && (humidity >= 13 && humidity <= 15) && (moisture >= 21 && moisture <= 40)) {
    return "Maize and Pulses";
  } else if ((temperature >= 21 && temperature <= 27) && (humidity >= 50 && humidity <= 60) && (moisture >= 45 && moisture <= 55)) {
    return "SugarCane";
  } else if ((temperature >= 20 && temperature <= 31) && (humidity >= 40 && humidity <= 60) && (moisture >= 3 && moisture <= 5)) {
    return "Tea";
  } else if ((temperature >= 17 && temperature <= 32) && (humidity >= 90 && humidity <= 95) && (moisture >= 95 && moisture <= 98)) {
    return "Cucumber";
  } else if ((temperature >= 10 && temperature <= 21) && (humidity >= 90 && humidity <= 95) && (moisture >= 90 && moisture <= 95)) {
    return "Cauliflower";
  } else if ((temperature >= 18 && temperature <= 29) && (humidity >= 85 && humidity <= 90) && (moisture >= 90 && moisture <= 95)) {
    return "Tomato";
  } else if ((temperature >= 15 && temperature <= 21) && (humidity >= 80 && humidity <= 95) && (moisture >= 75 && moisture <= 80)) {
    return "Potato";
  } else if ((temperature >= 24 && temperature <= 32) && (humidity >= 75 && humidity <= 90) && (moisture >= 90 && moisture <= 95)) {
    return "LadyFinger";
  } else if ((temperature >= 7 && temperature <= 25) && (humidity >= 88 && humidity <= 95) && (moisture >= 90 && moisture <= 95)) {
    return "Cabbage";
  } else if ((temperature >= 16 && temperature <= 30) && (humidity >= 50 && humidity <= 70) && (moisture >= 11 && moisture <= 13)) {
    return "Soyabean";
  } else if ((temperature >= 13 && temperature <= 27) && (humidity >= 65 && humidity <= 72) && (moisture >= 85 && moisture <= 92)) {
    return "Onion";
  } else if ((temperature >= 10 && temperature <= 29) && (humidity >= 80 && humidity <= 85) && (moisture >= 86 && moisture <= 92)) {
    return "Corriander";
  } else if ((temperature >= 25 && temperature <= 35) && (humidity >= 12 && humidity <= 22) && (moisture >= 50 && moisture <= 80)) {
    return "Groundnut";
  } else {
    return "";
  }
}

void DisplayCycle(String PhaseOneReading, String PhaseTwoReading, String PhaseThreeReading, String PhaseFourReading, String totalReading) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Germination:");
  lcd.setCursor(0, 1);
  lcd.print("0-3 weeks");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water Req(ltrs)");
  lcd.setCursor(0, 1);
  lcd.print(PhaseOneReading);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tillering:");
  lcd.setCursor(0, 1);
  lcd.print("3-8 weeks");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water Req(ltrs)");
  lcd.setCursor(0, 1);
  lcd.print(PhaseTwoReading);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Stem Extension:");
  lcd.setCursor(0, 1);
  lcd.print("8-15 weeks");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water Req(ltrs)");
  lcd.setCursor(0, 1);
  lcd.print(PhaseThreeReading);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Grain Filling:");
  lcd.setCursor(0, 1);
  lcd.print("15 - 20 weeks");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water Req(ltrs)");
  lcd.setCursor(0, 1);
  lcd.print(PhaseFourReading);
  delay(2000);


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Total Req:(ltr) ");
  lcd.setCursor(0, 1);
  lcd.print(totalReading);
  delay(3000);
}

void predictCropCultivationCycle(String crop) {
  // Replace this with your prediction logic
  if (crop == "Rice and Wheat" || crop == "Maize and Pulses") {
    DisplayCycle("22k - 32k", "112k - 162k", "157k - 227k", "157k - 250k", "450k - 650k");
  } else if (crop == "SugarCane" || crop == "Cucumber" || crop == "Tomato" || crop == "Potato" || crop == "LadyFinger" || crop == "Cabbage" || crop == "Onion" || crop == "Corriander") {
    DisplayCycle("15k - 32k", "115k - 162k", "160k - 227k", "172k - 250k", "450k - 720k");
  } else if (crop == "Soyabean") {
    DisplayCycle("15k - 25k", "120k - 125k", "130k - 175k", "170k - 182k", "350k - 380k");
  } else if (crop = "Groundnut") {
    DisplayCycle("9k - 17k", "115k - 121k", "125k - 130k", "150k - 1726k", "250k - 320k");
  }
  else if (crop = "") {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Crop to");
    lcd.setCursor(0, 1);
    lcd.print("Cultivation");
    delay(5000);
  }
}
// Rest of your code...
