/// Do not build debug mode. Define in UserConfig.h if desired.
// #define DEBUG

CONFIGURE(serialDebug, false)
CONFIGURE(ControlFansDAC, false)

// local network settings are external now
#include "UserConfigNetwork.h"


//#define NO_ETHERNET
//CONFIGURE(NetworkIPAddress, 192, 168, 1, 2)
//CONFIGURE(NetworkMACAddress, 0xDE, 0xAD, 0xCA, 0xFE, 0xBA, 0xBE)
//CONFIGURE(PrefixMQTT, "ap300")
//CONFIGURE(NetworkMQTTBroker, 192, 168, 1, 1)
//CONFIGURE(NetworkMQTTPort, 1883)
//CONFIGURE(NetworkMQTTUsername, "")
//CONFIGURE(NetworkMQTTPassword, "")

// R3G225-AE19-12 (Nenndrehzahl 2850 U/min)
CONFIGURE(StandardNenndrehzahlFan, 2850);
// Aus dem Protokoll der Wartung:
// Drehzahl für Standardlüftungsstufe Zuluft.
CONFIGURE(StandardSpeedSetpointFan1, 1150)
// Drehzahl für Standardlüftungsstufe Abluft.
CONFIGURE(StandardSpeedSetpointFan2, 1140)

/// Bypass Strom an/aus. Das BypassPower steuert, ob Strom am Bypass geschaltet ist, BypassDirection bestimmt Öffnen oder Schliessen.
CONFIGURE(PinBypassPower, 44)
/// Bypass Richtung, Stromlos = Schliessen (Winterstellung), Strom = Öffnen (Sommerstellung).
CONFIGURE(PinBypassDirection, 42)
/// Stromversorgung Lüfter 1.
CONFIGURE(PinFan1Power, 48)
/// Stromversorgung Lüfter 2.
CONFIGURE(PinFan2Power, 46)

/// Steuerung Lüfter Zuluft per PWM Signal.
CONFIGURE(PinFan1PWM, 5)
/// Steuerung Lüfter Abluft per PWM Signal.
CONFIGURE(PinFan2PWM, 6)
/// Steuerung Vorheizregister per PWM Signal.
CONFIGURE(PinPreheaterPWM, 45)
/// Eingang Lüfter Zuluft Tachosignal mit Interrupt, Zuordnung von Pin zu Interrupt geschieht im Code mit der Funktion digitalPinToInterrupt.
CONFIGURE(PinFan1Tacho, 19)
/// Eingang Lüfter Abluft Tachosignal mit Interrupt, Zuordnung von Pin zu Interrupt geschieht im Code mit der Funktion digitalPinToInterrupt.
CONFIGURE(PinFan2Tacho, 18)
/// Pin vom 1. DHT Sensor. 
CONFIGURE(PinDHTSensor1, 8)
/// Pin vom 2. DHT Sensor.
CONFIGURE(PinDHTSensor2, 9)
/// Input Sensor Aussenlufttemperatur.
CONFIGURE(PinTemp1OneWireBus, 26)
/// Input Sensor Zulufttemperatur.
CONFIGURE(PinTemp2OneWireBus, 30)
/// Input Sensor Ablufttemperatur.
CONFIGURE(PinTemp3OneWireBus, 34)
/// Input Sensor Fortlufttemperatur.
CONFIGURE(PinTemp4OneWireBus, 40)
/// Analog Pin für VOC Sensor.
CONFIGURE(PinVocSensor, A7)
// reset the EEPROM on startup
// CONFIGURE(FACTORY_RESET_EEPROM, true)

// ***************************************************  T F T / T O U C H   E I N S T E L L U N G E N *************************************************
// most mcufriend shields use these pins and Portrait mode:
  static constexpr uint8_t YP = A9;  // must be an analog pin, use "An" notation!
  static constexpr uint8_t XM = A10;  // must be an analog pin, use "An" notation!
  static constexpr uint8_t YM = 29;   // can be a digital pin
  static constexpr uint8_t XP = 31;   // can be a digital pin
