/*
 * Copyright (C) 2018 Sven Just (sven@familie-just.de)
 * Copyright (C) 2018 Ivan Schréter (schreter@gmx.net)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * This copyright notice MUST APPEAR in all copies of the software!
 */

/*!
 * @file
 * @brief Configuration of the project.
 *
 * @note DO NOT MODIFY THIS FILE. Put your configuration into UserConfig.h.
 *
 * If no UserConfig.h is provided, then defaults are used. If it is provided,
 * then defaults may be overridden there, by using lines in the form:
 *
 * CONFIGURE(name, value)
 * CONFIGURE(name, values...)
 *
 * for each configuration parameter from KWLConfig.
 *
 * File UserConfig.h is not tracked, so it's easy to define specific site
 * configuration without modifying the tracked source code. Most likely, you
 * will at least want to override network settings.
 *
 * @par Example:
 * @code
 * CONFIGURE(RelayOFF, OPEN)
 * CONFIGURE(NetworkIPAddress, 192, 168, 42, 201)
 * CONFIGURE(NetworkMACAddress, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF)
 * CONFIGURE(PrefixMQTT, "ap300")
 * @endcode
 *
 * You can also define DEBUG macro in UserConfig.h to enable debugging MQTT messages.
 */
#define DEBUG

#pragma once

#include "ProgramData.h"

#include <FlashStringLiteral.h>
#include <PersistentConfiguration.h>
#include <Arduino.h>

class IPAddress;
class HardwareSerial;

/// Helper to construct IP address as a literal.
class IPAddressLiteral
{
public:
  constexpr IPAddressLiteral() = default;
  constexpr IPAddressLiteral(byte a, byte b, byte c, byte d) noexcept : ip{a, b, c, d} {}
  operator IPAddress() const noexcept;
  constexpr IPAddressLiteral operator&(const IPAddressLiteral& other) const noexcept {
    return IPAddressLiteral(ip[0] & other.ip[0], ip[1] & other.ip[1], ip[2] & other.ip[2], ip[3] & other.ip[3]);
  }
  constexpr IPAddressLiteral operator|(const IPAddressLiteral& other) const noexcept {
    return IPAddressLiteral(ip[0] | other.ip[0], ip[1] | other.ip[1], ip[2] | other.ip[2], ip[3] | other.ip[3]);
  }
  IPAddressLiteral(const IPAddress& a) noexcept;
  constexpr byte operator[](unsigned index) const noexcept {
    return ip[index];
  }
  byte& operator[](unsigned index) noexcept {
    return ip[index];
  }
private:
  byte ip[4] = {0};
};

/// Helper to construct MAC address as a literal.
class MACAddressLiteral
{
public:
  constexpr MACAddressLiteral() = default;
  constexpr MACAddressLiteral(byte a, byte b, byte c, byte d, byte e, byte f) : mac{a, b, c, d, e,f} {}
  void copy_to(byte* out) const { out[0] = mac[0]; out[1] = mac[1]; out[2] = mac[2]; out[3] = mac[3]; out[4] = mac[4]; out[5] = mac[5]; }
  constexpr byte operator[](unsigned index) const noexcept {
    return mac[index];
  }
  byte& operator[](unsigned index) noexcept {
    return mac[index];
  }
private:
  byte mac[6] = {0};
};

/// State of the bypass flap.
enum class SummerBypassFlapState : uint8_t
{
  UNKNOWN = 0,  ///< Unknown.
  CLOSED  = 1,  ///< Closed or closing.
  OPEN    = 2   ///< Open or opening.
};

/// Summer bypass operation mode.
enum class SummerBypassMode : uint8_t
{
  AUTO    = 0,  ///< Open/close automatically.
  USER    = 1   ///< Open/close on external command.
};

/// Maximum # of fan mode settings. Not configurable.
static constexpr unsigned MAX_FAN_MODE_CNT = 10;

/// Do not build debug mode. Define in UserConfig.h if desired.
#undef DEBUG

/// Default configuration, which can be overridden by the user configuration below.
template<typename FinalConfig>
class KWLDefaultConfig
{
protected:
  /// Helper for relay state.
  static constexpr int8_t OPEN = -1;

public:

  // ***************************************************  V E R S I O N S N U M M E R   D E R    S W   *************************************************
  static constexpr auto VersionString = makeFlashStringLiteral("v0.22");


  // ***************************************************  N E T Z W E R K E I N S T E L L U N G E N *****************************************************
  // Hier die IP Adresse für diese Steuerung und den MQTT Broker definieren.

  /// MAC Adresse des Ethernet Shields.
  static constexpr MACAddressLiteral NetworkMACAddress = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };

  /// IP Adresse für diese Gerät im eigenen Netz.
  static constexpr IPAddressLiteral NetworkIPAddress = {192, 168,  20, 201};

  /// Subnet Mask.
  static constexpr IPAddressLiteral NetworkSubnetMask = {255, 255, 255,   0};

  /// Gateway, defaults to network address with "1" as last element.
  static constexpr IPAddressLiteral NetworkGateway = (FinalConfig::NetworkIPAddress & FinalConfig::NetworkSubnetMask) | IPAddressLiteral(0, 0, 0, 1);

  /// DNS Server, defaults to gateway.
  static constexpr IPAddressLiteral NetworkDNSServer = FinalConfig::NetworkGateway;

  /// NTP (network time protocol) server, defaults to gateway.
  static constexpr IPAddressLiteral NetworkNTPServer = FinalConfig::NetworkGateway;

  /// IP Adresse des MQTT Brokers.
  static constexpr IPAddressLiteral NetworkMQTTBroker = {192, 168,  20, 240};

  /// Port des MQTT Brokers.
  static constexpr uint16_t NetworkMQTTPort = 1883;

  /// Login name für den MQTT Broker.
  static constexpr const char* NetworkMQTTUsername = nullptr;

  /// Passwort für den MQTT Broker.
  static constexpr const char* NetworkMQTTPassword = nullptr;

  /// Prefix for all messages to and from the controller.
  static constexpr auto PrefixMQTT = makeFlashStringLiteral("d15");

  // *******************************************E N D E ***  N E T Z W E R K E I N S T E L L U N G E N **************************************************


  // ***************************************************  T F T / T O U C H   E I N S T E L L U N G E N *************************************************

  // most mcufriend shields use these pins and Portrait mode:
  static constexpr uint8_t YP = A1;  // must be an analog pin, use "An" notation!
  static constexpr uint8_t XM = A2;  // must be an analog pin, use "An" notation!
  static constexpr uint8_t YM = 7;   // can be a digital pin
  static constexpr uint8_t XP = 6;   // can be a digital pin

  /// Orientation of the TFT display.
  static constexpr uint8_t TFTOrientation = 3;    //PORTRAIT

  // *******************************************E N D E ***  T F T / T O U C H   E I N S T E L L U N G E N **********************************************


  // ******************************************* W E R K S E I N S T E L L U N G E N ********************************************************************
  // Definition der Werkseinstellungen.
  // Es können bis zu 10 Lüftungsstufen definiert werden. Im Allgemeinen sollten 4 oder 6 Stufen ausreichen.
  // Die Originalsteuerung stellt 3 Stufen zur Verfügung
  //
  // Eine Definition für 4 Stufen, ähnlich der Originalsteuerung wäre:
  // Stufe 0 = 0%, Stufe 1 = 70%, Stufe 2 = 100%, Stufe 3 = 130%. Stufe 0 ist hier zusätzlich.
  //
  // Ein mögliche Definition für 6 Stufen wäre bspw.:
  // Stufe 0 = 0%, Stufe 1 = 60%, Stufe 2 = 80%, Stufe 3 = 100%, Stufe 4 = 120%, Stufe 5 = 140%

  /// # der konfigurierten Standardlüftungsstufen.
  static constexpr unsigned StandardModeCnt = 4;
  /// Solldrehzahlen in Relation zur Standardlüftungsstufe.
  static constexpr double StandardKwlModeFactor[MAX_FAN_MODE_CNT] = {0, 0.7, 1, 1.3};
  /// Standardlüftungsstufe beim Anschalten.
  static constexpr int StandardKwlMode = 2;
  /// Drehzahl für Standardlüftungsstufe Zuluft.
  static constexpr unsigned StandardSpeedSetpointFan1       = 1550;              // sju: 1450
  /// Drehzahl für Standardlüftungsstufe Abluft.
  static constexpr unsigned StandardSpeedSetpointFan2       = 1550;              // sju: 1100
  /// Adjustment for computing RPM of fan 1 (impulses per rotation), if tacho signal is not sent 1:1 for each rotation.
  static constexpr float StandardFan1ImpulsesPerRotation    = 1.0;
  /// Adjustment for computing RPM of fan 2 (impulses per rotation), if tacho signal is not sent 1:1 for each rotation.
  static constexpr float StandardFan2ImpulsesPerRotation    = 1.0;
  /// Max Abweichung der Istdrehzahl zur Solldrehzahl bei Kalibrierung in Prozent
  static constexpr double StandardKwlFanPrecisionPercent    = 1.5;
  /// Nenndrehzahl Papst Lüfter lt Datenblatt 3200 U/min.
  static constexpr unsigned StandardNenndrehzahlFan         = 3200;
  /// Mindestablufttemperatur für die Öffnung des Bypasses im Automatik Betrieb.
  static constexpr unsigned StandardBypassTempAbluftMin     =   24;
  /// Mindestaussenlufttemperatur für die Öffnung des Bypasses im Automatik Betrieb.
  static constexpr unsigned StandardBypassTempAussenluftMin =   13;
  /// Hystereszeit für eine Umstellung des Bypasses im Automatik Betrieb.
  static constexpr unsigned StandardBypassHystereseMinutes  =   60;
  /// Hysteretemperatur für eine Umstellung des Bypasses im Automatik Betrieb.
  static constexpr unsigned StandardBypassHysteresisTemp    =    2;
  /// Stellung der Bypassklappen im manuellen Betrieb (1 = Close).
  static constexpr unsigned StandardBypassManualSetpoint    =    1;
  /// Automatik oder manueller Betrieb der Bypassklappe (0 = Auto).
  // Im Automatikbetrieb steuert diese Steuerung die Bypass-Klappe, im manuellen Betrieb wird die Bypass-Klappe durch mqtt-Kommandos gesteuert.
  static constexpr unsigned StandardBypassMode              =    0;
  /// Hysteretemperatur für Steuerung von Antifreeze.
  static constexpr unsigned StandardAntifreezeHystereseTemp =    3;
  /// House with fireplace.
  static constexpr bool StandardHeatingAppCombUse           = false;

  /// Daylight savings time default settings.
  static constexpr bool StandardDST                         = false;
  /// Standard time zone offset in minutes (CET, GMT+1).
  static constexpr int16_t StandardTimezoneMin              = 60;

  /// Maximum number of programs.
  static constexpr uint8_t MaxProgramCount = 16;

  /// Maximum number of crash reports.
  static constexpr uint8_t MaxCrashReportCount = 4;

  /*!
   * @brief Perform "factory reset" *at each startup*.
   *
   * If set, perform load of defaults on each startup. If not set, load EEPROM data.
   * DO NOT set this in productive environment, only as last resort to reset EEPROM.
   *
   * Factory reset can be also done using MQTT:
   * @code
   * mosquitto_pub -t d15/set/kwl/resetAll_IKNOWWHATIMDOING -m YES
   * @endcode
   */
  static constexpr bool FACTORY_RESET_EEPROM = false;

  /// EEPROM configuration version to expect/write.
  static constexpr unsigned KWL_EEPROM_VERSION = 49;

  // **************************************E N D E *** W E R K S E I N S T E L L U N G E N **************************************************************


  // ***************************************************  A N S C H L U S S E I N S T E L L U N G E N ***************************************************
  // Die Anschlüsse können dem Schaltplan entnommen werden: https://github.com/svenjust/room-ventilation-system/blob/master/Docs/circuit%20diagram/KWL-Steuerung%20f%C3%BCr%20P300.pdf

  /// Bypass Strom an/aus. Das BypassPower steuert, ob Strom am Bypass geschaltet ist, BypassDirection bestimmt Öffnen oder Schliessen.
  static constexpr uint8_t PinBypassPower     = 40;
  /// Bypass Richtung, Stromlos = Schliessen (Winterstellung), Strom = Öffnen (Sommerstellung).
  static constexpr uint8_t PinBypassDirection = 41;
  /// Stromversorgung Lüfter 1.
  static constexpr uint8_t PinFan1Power       = 42;
  /// Stromversorgung Lüfter 2.
  static constexpr uint8_t PinFan2Power       = 43;

  /// Steuerung Lüfter Zuluft per PWM Signal.
  static constexpr uint8_t PinFan1PWM         = 44;
  /// Steuerung Lüfter Abluft per PWM Signal.
  static constexpr uint8_t PinFan2PWM         = 46;
  /// Steuerung Vorheizregister per PWM Signal.
  static constexpr uint8_t PinPreheaterPWM    = 45;
  /// Eingang Lüfter Zuluft Tachosignal mit Interrupt, Zuordnung von Pin zu Interrupt geschieht im Code mit der Funktion digitalPinToInterrupt.
  static constexpr uint8_t PinFan1Tacho       = 18;
  /// Eingang Lüfter Abluft Tachosignal mit Interrupt, Zuordnung von Pin zu Interrupt geschieht im Code mit der Funktion digitalPinToInterrupt.
  static constexpr uint8_t PinFan2Tacho       = 19;
  /// Sampling für Tachoimpulse beim FALLING oder RISING.
  static constexpr int8_t TachoSamplingMode   = RISING;

  // Alternative zu PWM, Ansteuerung per DAC. I2C nutzt beim Arduino Mega Pin 20 u 21.
  /// I2C-OUTPUT-Addresse für Horter DAC als 7 Bit, wird verwendet als Alternative zur PWM Ansteuerung der Lüfter und für Vorheizregister.
  static constexpr uint8_t DacI2COutAddr       = 176 >> 1;
  /// Kanal 1 des DAC für Zuluft.
  static constexpr uint8_t DacChannelFan1      = 0;
  /// Kanal 2 des DAC für Abluft.
  static constexpr uint8_t DacChannelFan2      = 1;
  /// Kanal 3 des DAC für Vorheizregister.
  static constexpr uint8_t DacChannelPreheater = 2;
  /// Zusätzliche Ansteuerung durch DAC über SDA und SLC (und PWM)
  static constexpr bool ControlFansDAC = true;

  /// Pin vom 1. DHT Sensor.
  static constexpr uint8_t PinDHTSensor1       = 28;
  /// Pin vom 2. DHT Sensor.
  static constexpr uint8_t PinDHTSensor2       = 29;

  // Für jeder Temperatursensor gibt es einen Anschluss auf dem Board, Vorteil: Temperatursensoren können per Kabel definiert werden, nicht Software
  /// Input Sensor Aussenlufttemperatur.
  static constexpr uint8_t PinTemp1OneWireBus  = 30;
  /// Input Sensor Zulufttemperatur.
  static constexpr uint8_t PinTemp2OneWireBus  = 31;
  /// Input Sensor Ablufttemperatur.
  static constexpr uint8_t PinTemp3OneWireBus  = 32;
  /// Input Sensor Fortlufttemperatur.
  static constexpr uint8_t PinTemp4OneWireBus  = 33;

  /// Analog Pin für VOC Sensor.
  static constexpr uint8_t PinVocSensor        = A15;
  /// CO2 Sensor (Winsen MH-Z14) wird über die Zweite Serielle Schnittstelle (Serial2) angeschlossen.
  // Serial2 nutzt beim Arduino Mega Pin 16 u 17
  static constexpr HardwareSerial& SerialMHZ14 = Serial2;

  // ******************************************* E N D E   A N S C H L U S S E I N S T E L L U N G E N **************************************************

  // ************************************** A N S T E U E R U N G   D E R    R E L A I S ****************************************************************
  // Für die Lüfter und den Sommer-Bypass können bis zu vier Relais verbaut sein.
  // Ohne Sommer-Bypass kann die Schaltung auch ohne Relais betrieben werden.
  // Da verschiedene Relais unterschiedlich geschaltet werden, kann hier die logische
  // Schaltung definiert werden (LOW, HIGH oder OPEN für high-impedance mode).

  /// Relay pin digital output needed to close the relay (HIGH/LOW/OPEN).
  static constexpr int8_t RelayON = LOW;
  /// Relay pin digital output needed to open the relay (HIGH/LOW/OPEN).
  static constexpr int8_t RelayOFF = HIGH;

  // ************************************** E N D E   A N S T E U E R U N G   D E R    R E L A I S ******************************************************

  // ************************************** M Q T T   R E P O R T I N G *********************************************************************************

  /// Period for sending heartbeat messages. Set to 0 to not send heartbeat.
  static constexpr uint8_t HeartbeatPeriod = 30;

  /// Send timestamp as heartbeat.
  static constexpr bool HeartbeatTimestamp = false;

  /// At most how often to send temperature messages via MQTT, in seconds.
  static constexpr uint8_t MinIntervalMqttTemp = 5;
  /// At least how often to send temperature messages via MQTT, in seconds.
  static constexpr uint8_t MaxIntervalMqttTemp = 60;
  /// Minimum change in temperature to report per MQTT.
  static constexpr double MinDiffMqttTemp = 0.1;

  /// Default for retain last measurements reading in the MQTT broker.
  static constexpr bool RetainMeasurements = true;

  /// Retain last temperature reading in the MQTT broker.
  static const bool RetainTemperature;

  /// Retain last additional sensors reading in the MQTT broker.
  static const bool RetainAdditionalSensors;

  /// Retain last fan mode reading in the MQTT broker.
  static const bool RetainFanMode;

  /// Retain last fan speed reading in the MQTT broker.
  static const bool RetainFanSpeed;

  /// Retain last antifreeze state reading in the MQTT broker.
  static const bool RetainAntifreezeState;

  /// Retain last bypass state reading in the MQTT broker.
  static const bool RetainBypassState;

  /// Retain last bypass configuration state reading in the MQTT broker.
  static const bool RetainBypassConfigState;

  /// Retain program configuration in the MQTT broker.
  static const bool RetainProgram;

  /// Retain last status bits readings in the MQTT broker.
  static const bool RetainStatusBits;

  /// If set, also erroneous measurements (like -127C for temperature) will be sent.
  static constexpr bool SendErroneousMeasurement = false;

  // ************************************** E N D E   M Q T T   R E P O R T I N G ***********************************************************************

  // ***************************************************  D E B U G E I N S T E L L U N G E N ********************************************************
  // Serial port speed to configure at startup.
  static constexpr uint32_t SerialSpeed = 57600;
  // Allgemeine Debugausgaben auf der seriellen Schnittstelle aktiviert.
  static constexpr bool serialDebug = false;
  // Debugausgaben für die Lüfter auf der seriellen Schnittstelle aktiviert.
  static constexpr bool serialDebugFan = false;
  // Debugausgaben für die Antifreezeschaltung auf der seriellen Schnittstelle aktiviert.
  static constexpr bool serialDebugAntifreeze = false;
  // Debugausgaben für die Summerbypassschaltung auf der seriellen Schnittstelle aktiviert.
  static constexpr bool serialDebugSummerbypass = false;
  // Debugausgaben für die Displayanzeige.
  static constexpr bool serialDebugDisplay = false;
  // Debugausgaben für die Sensoren.
  static constexpr bool serialDebugSensor = false;
  // Debugausgaben für das Programm.
  static constexpr bool serialDebugProgram = false;
  // *******************************************E N D E ***  D E B U G E I N S T E L L U N G E N *****************************************************
};

template<typename FinalConfig>
constexpr FlashStringLiteral<6> KWLDefaultConfig<FinalConfig>::VersionString;

template<typename FinalConfig>
constexpr MACAddressLiteral KWLDefaultConfig<FinalConfig>::NetworkMACAddress;
template<typename FinalConfig>
constexpr IPAddressLiteral KWLDefaultConfig<FinalConfig>::NetworkIPAddress;
template<typename FinalConfig>
constexpr IPAddressLiteral KWLDefaultConfig<FinalConfig>::NetworkSubnetMask;
template<typename FinalConfig>
constexpr IPAddressLiteral KWLDefaultConfig<FinalConfig>::NetworkGateway;
template<typename FinalConfig>
constexpr IPAddressLiteral KWLDefaultConfig<FinalConfig>::NetworkDNSServer;
template<typename FinalConfig>
constexpr IPAddressLiteral KWLDefaultConfig<FinalConfig>::NetworkNTPServer;
template<typename FinalConfig>
constexpr IPAddressLiteral KWLDefaultConfig<FinalConfig>::NetworkMQTTBroker;
template<typename FinalConfig>
const bool KWLDefaultConfig<FinalConfig>::RetainTemperature = FinalConfig::RetainMeasurements;
template<typename FinalConfig>
const bool KWLDefaultConfig<FinalConfig>::RetainAdditionalSensors = FinalConfig::RetainMeasurements;
template<typename FinalConfig>
const bool KWLDefaultConfig<FinalConfig>::RetainFanMode = FinalConfig::RetainMeasurements;
template<typename FinalConfig>
const bool KWLDefaultConfig<FinalConfig>::RetainFanSpeed = FinalConfig::RetainMeasurements;
template<typename FinalConfig>
const bool KWLDefaultConfig<FinalConfig>::RetainAntifreezeState = FinalConfig::RetainMeasurements;
template<typename FinalConfig>
const bool KWLDefaultConfig<FinalConfig>::RetainBypassState = FinalConfig::RetainMeasurements;
template<typename FinalConfig>
const bool KWLDefaultConfig<FinalConfig>::RetainBypassConfigState = FinalConfig::RetainMeasurements;
template<typename FinalConfig>
const bool KWLDefaultConfig<FinalConfig>::RetainProgram = FinalConfig::RetainMeasurements;
template<typename FinalConfig>
const bool KWLDefaultConfig<FinalConfig>::RetainStatusBits = FinalConfig::RetainMeasurements;

/// Helper template to convert user-defined configuration objects.
template<typename T> struct UserConfig {
  static constexpr T make(const T value) noexcept { return value; }
};

// specialization for strings
template<size_t OrigLen> struct UserConfig<const FlashStringLiteral<OrigLen>> {
  template<size_t Len>
  static constexpr FlashStringLiteral<Len> make(const char (&s)[Len]) noexcept { return makeFlashStringLiteral(s); }
};

// specialization for IP address
template<> struct UserConfig<const IPAddressLiteral> {
  static constexpr IPAddressLiteral make(uint8_t a, uint8_t b, uint8_t c, uint8_t d) noexcept { return IPAddressLiteral(a, b, c, d); }
};

// specialization for MAC address
template<> struct UserConfig<const MACAddressLiteral> {
  static constexpr MACAddressLiteral make(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f) noexcept { return MACAddressLiteral(a, b, c, d, e, f); }
};

/*!
 * @brief Helper macro to add configuration in UserConfig.h.
 *
 * If you get an error here, this means that you probably mistyped a configuration parameter name
 * from KWLDefaultConfig or the value is not compatible for the data type.
 *
 * @param name configuration parameter name.
 * @param ... value(s) for the parameter (simple value or comma-separated list, e.g., for IP address).
 */
#define CONFIGURE(name, ...) static constexpr auto name = UserConfig<decltype(KWLDefaultConfig<KWLConfig>::name)>::make(__VA_ARGS__);

/// Actual configuration, including user-specific values.
class KWLConfig : public KWLDefaultConfig<KWLConfig>
{
public:
#if !__has_include("UserConfig.h")
#pragma message("No UserConfig.h provided, using only defaults. Most likely you want local configuration. See KWLConfig.h for instructions.")
#else
#include "UserConfig.h"
#endif
};

template<typename FinalConfig>
constexpr double KWLDefaultConfig<FinalConfig>::StandardKwlModeFactor[MAX_FAN_MODE_CNT];

// Helper for getters and setters.
#define KWL_GETSET(name) \
  decltype(name##_) get##name() const { return name##_; } \
  void set##name(decltype(name##_) value) { name##_ = value; update(name##_); }

// Helper for getters and setters.
#define KWL_GETSET2(name, var) \
  decltype(var) get##name() const { return var; } \
  void set##name(decltype(var) value) { var = value; update(var); }

// Helper for getters and setters.
#define KWL_GETSET3(name, var, type) \
  type get##name() const { return type(var); } \
  void set##name(type value) { var = decltype(var)(value); update(var); }

/// Structure used to store crash data in EEPROM.
struct CrashData
{
  uint32_t millis;        ///< millis() at the time of the crash.
  uint32_t real_time;     ///< Real time (via NTP) if available at the time of the crash.
  uint32_t crash_addr:18; ///< Crash address (instruction pointer).
  uint32_t crash_sp:14;   ///< SP at the time of crash.
};

/// Touchscreen calibration settings.
struct TouchCalibration
{
  /// Signal mapping to left/right boundaries.
  uint16_t left_, right_;
  /// Signal mapping to top/bottom boundaries.
  uint16_t top_, bottom_;
  /// X/Y swap flag.
  bool swap_xy_;
  /// Calibration flag.
  bool calibrated_;

  /// Reset contained calibration.
  void reset(int16_t w = 1000, int16_t h = 1000) {
    left_ = 0;
    right_ = uint16_t(w);
    top_ = 0;
    bottom_ = uint16_t(h);
    swap_xy_ = false;
    calibrated_ = false;
  }
};

/*!
 * @brief Persistent configuration of the ventilation system.
 */
class KWLPersistentConfig : public PersistentConfiguration<KWLPersistentConfig, KWLConfig::KWL_EEPROM_VERSION>
{
private:
  friend class PersistentConfiguration<KWLPersistentConfig, KWLConfig::KWL_EEPROM_VERSION>;

  // documentation see KWLConfig

  // NOTE: this is PERSISTENT layout, do not reorder unless you increase the version number
  unsigned SpeedSetpointFan1_;        // 2
  unsigned SpeedSetpointFan2_;        // 4
  unsigned BypassTempAbluftMin_;      // 6
  unsigned BypassTempAussenluftMin_;  // 8
  unsigned BypassHystereseMinutes_;   // 10
  unsigned AntifreezeHystereseTemp_;  // 12
  unsigned BypassManualSetpoint_;     // 14
  unsigned BypassMode_;               // 16
  bool DST_;                          // 18
  uint8_t BypassHysteresisTemp_;      // 19
  int FanPWMSetpoint_[10][2];         // 20-59
  bool HeatingAppCombUse_;            // 60
  uint8_t program_set_index_;         // 61
  int16_t TimezoneMin_;               // 62
  ProgramData programs_[KWLConfig::MaxProgramCount];  // 64..192
  CrashData crashes_[KWLConfig::MaxCrashReportCount]; // 192..240

  // Network configuration:
  char mqtt_prefix_[8];               // 240..248
  IPAddressLiteral ip_;               // 248
  IPAddressLiteral netmask_;          // 252
  IPAddressLiteral gw_;               // 256
  IPAddressLiteral dns_;              // 260
  IPAddressLiteral mqtt_;             // 264
  uint16_t mqtt_port_;                // 268
  IPAddressLiteral ntp_;              // 270
  MACAddressLiteral mac_;             // 274

  // Touchscreen configuration
  TouchCalibration touch_;            // 280..290

  // Fan RPM adjustment configuration
  float Fan1ImpulsesPerRotation_;              // 290
  float Fan2ImpulsesPerRotation_;              // 294
  // 298

  /// Initialize with defaults, if version doesn't fit.
  void loadDefaults();

  /// Initialize network default values.
  void loadNetworkDefaults();

  /// Migrate configuration.
  void migrate();

public:
  // default getters/setters
  KWL_GETSET(SpeedSetpointFan1)
  KWL_GETSET(SpeedSetpointFan2)
  KWL_GETSET(Fan1ImpulsesPerRotation)
  KWL_GETSET(Fan2ImpulsesPerRotation)
  KWL_GETSET(BypassTempAbluftMin)
  KWL_GETSET(BypassTempAussenluftMin)
  KWL_GETSET(BypassHystereseMinutes)
  KWL_GETSET(BypassHysteresisTemp)
  KWL_GETSET3(BypassManualSetpoint, BypassManualSetpoint_, SummerBypassFlapState)
  KWL_GETSET3(BypassMode, BypassMode_, SummerBypassMode)
  KWL_GETSET(AntifreezeHystereseTemp)
  KWL_GETSET(DST)
  KWL_GETSET(HeatingAppCombUse)
  KWL_GETSET(TimezoneMin)

  KWL_GETSET2(NetworkMACAddress, mac_)
  KWL_GETSET2(NetworkIPAddress, ip_)
  KWL_GETSET2(NetworkSubnetMask, netmask_)
  KWL_GETSET2(NetworkGateway, gw_)
  KWL_GETSET2(NetworkDNSServer, dns_)
  KWL_GETSET2(NetworkNTPServer, ntp_)
  KWL_GETSET2(NetworkMQTTBroker, mqtt_)
  KWL_GETSET2(NetworkMQTTPort, mqtt_port_)

  int getFanPWMSetpoint(unsigned fan, unsigned idx) { return FanPWMSetpoint_[idx][fan]; }
  void setFanPWMSetpoint(unsigned fan, unsigned idx, int pwm) { FanPWMSetpoint_[idx][fan] = pwm; update(FanPWMSetpoint_[idx][fan]); }

  /// Get program data from the given slot.
  const ProgramData& getProgram(unsigned index) const { return programs_[index]; }

  /// Get current program set index.
  uint8_t getProgramSetIndex() const { return program_set_index_; }

  /// Set current program set index.
  void setProgramSetIndex(uint8_t index) { program_set_index_ = index; update(program_set_index_); }

  /// Check if any crash report is present.
  bool hasCrash() const;

  /// Get crash data from given slot.
  const CrashData& getCrash(unsigned index) const { return crashes_[index]; }

  /// Store a crash report, overwriting oldest slot as necessary.
  void storeCrash(uint32_t pc, unsigned sp, uint32_t real_time);

  /// Reset all crash data.
  void resetCrashes();

  /// Set program data in the given slot.
  void setProgram(unsigned index, const ProgramData& program) { programs_[index] = program; update(programs_[index]); }

  /// Enable or disable program data in the given slot.
  void enableProgram(unsigned index, uint8_t mask) { programs_[index].enable(mask); update(programs_[index].enabled_progsets_); }

  /// Get prefix for all MQTT messages.
  const char* getMQTTPrefix() const { return mqtt_prefix_; }

  /// Set prefix for all MQTT messages.
  bool setMQTTPrefix(const char* prefix);

  /// Get TFT calibration.
  const TouchCalibration& getTouchCalibration() const { return touch_; }

  /// Set new TFT calibration.
  void setTouchCalibration(const TouchCalibration& touch) { touch_ = touch; update(touch_); }
};

#undef KWL_GETSET
