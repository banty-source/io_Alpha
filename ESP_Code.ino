#include <LiquidCrystal.h>  // Include library for 16x2 LCD

// Initialize the LCD (RS, EN, D4, D5, D6, D7) connected to digital pins of ESP32
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Pin definitions
const int waterSensorPin = A0;  // Analog pin for the water sensor
const int relayPin = 0;         // Digital pin for relay control
const int motorPin = 4;         // Digital pin for motor control via relay

// Water level threshold value (adjust based on sensor calibration)
const int waterThreshold = 500;  

// Variable to store the current water level
int waterLevel = 0; 

void setup() {
  // Initialize the LCD (16 columns, 2 rows)
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Water Monitor");

  // Set pin modes
  pinMode(waterSensorPin, INPUT);  // Water sensor pin as INPUT
  pinMode(relayPin, OUTPUT);       // Relay control pin as OUTPUT
  pinMode(motorPin, OUTPUT);       // Motor control pin as OUTPUT

  // Start with pump OFF
  digitalWrite(relayPin, LOW);
  digitalWrite(motorPin, LOW);

  delay(2000);  // Display the welcome message for 2 seconds
  lcd.clear();  // Clear the LCD display
}

void loop() {
  // Read the water sensor value
  waterLevel = analogRead(waterSensorPin);

  // Display water level on LCD
  lcd.setCursor(0, 0);
  lcd.print("Water Level: ");
  lcd.setCursor(12, 0);
  lcd.print(waterLevel);  // Display sensor value

  // Check the water level against the threshold
  if (waterLevel < waterThreshold) {
    activatePump();
  } else {
    deactivatePump();
  }

  delay(1000);  // Wait for 1 second before the next reading
}

// Function to activate the pump
void activatePump() {
  digitalWrite(relayPin, HIGH);  // Turn ON the relay
  digitalWrite(motorPin, HIGH);  // Turn ON the motor
  lcd.setCursor(0, 1);
  lcd.print("Pump: ON  ");       // Display pump status
}

// Function to deactivate the pump
void deactivatePump() {
  digitalWrite(relayPin, LOW);   // Turn OFF the relay
  digitalWrite(motorPin, LOW);   // Turn OFF the motor
  lcd.setCursor(0, 1);
  lcd.print("Pump: OFF ");       // Display pump status
}
