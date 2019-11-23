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
 * @brief MQTT topics for communication with outside world.
 */

#pragma once

#include <FlashStringLiteral.h>

/*!
 * @brief MQTT Topics für die Kommunikation zwischen dieser Steuerung und einem mqtt Broker.
 *
 * Die Topics sind in https://github.com/svenjust/room-ventilation-system/blob/master/Docs/mqtt%20topics/mqtt_topics.ods erläutert.
 */
namespace MQTTTopic
{
  // Global paths. These are prefixed with MQTT prefix (default: d15)

  /// Path for all normal commands. Also used for subscribing.
  constexpr auto Command                    = makeFlashStringLiteral("/set/kwl/");
  /// Path for all debug commands. Also used for subscribing.
  constexpr auto CommandDebug               = makeFlashStringLiteral("/debugset/kwl/");
  /// Path for all status values.
  constexpr auto State                      = makeFlashStringLiteral("/state/kwl/");
  /// Path for all debug status values.
  constexpr auto StateDebug                 = makeFlashStringLiteral("/debugstate/kwl/");

  /// Switch to simulation mode for debuggable values.
  constexpr auto ValueSimulate              = makeFlashStringLiteral("simulate");
  /// Switch to real measurement mode for debuggable values.
  constexpr auto ValueMeasure               = makeFlashStringLiteral("measure");

  // Remaining commands/values are internally prefixed by Command/State or by
  // CommandDebug/StateDebug. To differentiate, debug commands and states are
  // prefixed by single '/' below.

  constexpr auto CmdResetAll                = makeFlashStringLiteral("resetAll_IKNOWWHATIMDOING");
  constexpr auto CmdRestart                 = makeFlashStringLiteral("restart");
  constexpr auto CmdInstallPrefix           = makeFlashStringLiteral("install/prefix");
  constexpr auto CmdCalibrateFans           = makeFlashStringLiteral("calibratefans");
  constexpr auto CmdFansCalculateSpeedMode  = makeFlashStringLiteral("fans/calculatespeed");
  constexpr auto CmdFan1Speed               = makeFlashStringLiteral("fan1/standardspeed");
  constexpr auto CmdFan2Speed               = makeFlashStringLiteral("fan2/standardspeed");
  constexpr auto CmdGetSpeed                = makeFlashStringLiteral("fans/getspeed");
  constexpr auto CmdGetTemp                 = makeFlashStringLiteral("temperatur/gettemp");
  constexpr auto CmdGetvalues               = makeFlashStringLiteral("getvalues");
  constexpr auto CmdMode                    = makeFlashStringLiteral("lueftungsstufe");
  constexpr auto CmdAntiFreezeHyst          = makeFlashStringLiteral("antifreeze/hysterese");
  constexpr auto CmdBypassGetValues         = makeFlashStringLiteral("summerbypass/getvalues");
  constexpr auto CmdBypassManualFlap        = makeFlashStringLiteral("summerbypass/flap");
  constexpr auto CmdBypassMode              = makeFlashStringLiteral("summerbypass/mode");
  constexpr auto CmdBypassHystereseMinutes  = makeFlashStringLiteral("summerbypass/HystereseMinutes");
  constexpr auto CmdBypassHyst              = makeFlashStringLiteral("summerbypass/HysteresisTemp");
  constexpr auto CmdBypassTempAbluftMin     = makeFlashStringLiteral("summerbypass/TempAbluftMin");
  constexpr auto CmdBypassTempAussenluftMin = makeFlashStringLiteral("summerbypass/TempAussenluftMin");
  constexpr auto CmdHeatingAppCombUse       = makeFlashStringLiteral("heatingapp/combinedUse");
  constexpr auto CmdSetProgram              = makeFlashStringLiteral("program/");
  constexpr auto CmdSetProgramSet           = makeFlashStringLiteral("program/set");
  constexpr auto SubtopicProgramData        = makeFlashStringLiteral("data");
  constexpr auto SubtopicProgramEnable      = makeFlashStringLiteral("enable");
  constexpr auto SubtopicProgramGet         = makeFlashStringLiteral("get");
  constexpr auto CmdScreenshot              = makeFlashStringLiteral("screenshot");
  constexpr auto CmdScreen                  = makeFlashStringLiteral("screen");
  constexpr auto CmdTouch                   = makeFlashStringLiteral("touch");

  constexpr auto Heartbeat                  = makeFlashStringLiteral("heartbeat");
  constexpr auto StatusBits                 = makeFlashStringLiteral("statusbits");
  constexpr auto Fan1Speed                  = makeFlashStringLiteral("fan1/speed");
  constexpr auto Fan2Speed                  = makeFlashStringLiteral("fan2/speed");
  constexpr auto StateKwlMode               = makeFlashStringLiteral("lueftungsstufe");
  constexpr auto KwlTemperaturAussenluft    = makeFlashStringLiteral("aussenluft/temperatur");
  constexpr auto KwlTemperaturZuluft        = makeFlashStringLiteral("zuluft/temperatur");
  constexpr auto KwlTemperaturAbluft        = makeFlashStringLiteral("abluft/temperatur");
  constexpr auto KwlTemperaturFortluft      = makeFlashStringLiteral("fortluft/temperatur");
  constexpr auto KwlEffiency                = makeFlashStringLiteral("effiencyKwl");
  constexpr auto KwlAntifreeze              = makeFlashStringLiteral("antifreeze");
  constexpr auto KwlBypassState             = makeFlashStringLiteral("summerbypass/flap");
  constexpr auto KwlBypassMode              = makeFlashStringLiteral("summerbypass/mode");
  constexpr auto KwlBypassTempAbluftMin     = makeFlashStringLiteral("summerbypass/TempAbluftMin");
  constexpr auto KwlBypassTempAussenluftMin = makeFlashStringLiteral("summerbypass/TempAussenluftMin");
  constexpr auto KwlBypassHystereseMinutes  = makeFlashStringLiteral("summerbypass/HystereseMinutes");
  constexpr auto KwlBypassHysteresisTemp    = makeFlashStringLiteral("summerbypass/HysteresisTemp");
  constexpr auto KwlHeatingAppCombUse       = makeFlashStringLiteral("heatingapp/combinedUse");
  constexpr auto KwlProgramIndex            = makeFlashStringLiteral("program/index");
  constexpr auto KwlProgramSet              = makeFlashStringLiteral("program/set");
  constexpr auto KwlProgramData             = makeFlashStringLiteral("program/");

  constexpr auto KwlDHT1Temperatur          = makeFlashStringLiteral("dht1/temperatur");
  constexpr auto KwlDHT2Temperatur          = makeFlashStringLiteral("dht2/temperatur");
  constexpr auto KwlDHT1Humidity            = makeFlashStringLiteral("dht1/humidity");
  constexpr auto KwlDHT2Humidity            = makeFlashStringLiteral("dht2/humidity");
  constexpr auto KwlCO2Abluft               = makeFlashStringLiteral("abluft/co2");
  constexpr auto KwlVOCAbluft               = makeFlashStringLiteral("abluft/voc");
  constexpr auto KwlDP1Pressure             = makeFlashStringLiteral("dp1/pressure");
  constexpr auto KwlDP2Pressure             = makeFlashStringLiteral("dp2/pressure");


  // Die folgenden Topics sind nur für die SW-Entwicklung, und schalten Debugausgaben per mqtt ein und aus
  constexpr auto KwlDebugsetFan1Getvalues   = makeFlashStringLiteral("/fan1/getvalues");
  constexpr auto KwlDebugsetFan2Getvalues   = makeFlashStringLiteral("/fan2/getvalues");
  constexpr auto KwlDebugstateFan1          = makeFlashStringLiteral("/fan1");
  constexpr auto KwlDebugstateFan2          = makeFlashStringLiteral("/fan2");
  constexpr auto KwlDebugstatePreheater     = makeFlashStringLiteral("/preheater");

  // Die folgenden Topics sind nur für die SW-Entwicklung, es werden Messwerte überschrieben,
  // es kann damit der Sommer-Bypass und die Frostschutzschaltung getestet werden
  constexpr auto KwlDebugsetTemperaturAussenluft = makeFlashStringLiteral("/aussenluft/temperatur");
  constexpr auto KwlDebugsetTemperaturZuluft     = makeFlashStringLiteral("/zuluft/temperatur");
  constexpr auto KwlDebugsetTemperaturAbluft     = makeFlashStringLiteral("/abluft/temperatur");
  constexpr auto KwlDebugsetTemperaturFortluft   = makeFlashStringLiteral("/fortluft/temperatur");

  constexpr auto KwlDebugsetT1              = makeFlashStringLiteral("/t1");
  constexpr auto KwlDebugsetT2              = makeFlashStringLiteral("/t2");
  constexpr auto KwlDebugsetT3              = makeFlashStringLiteral("/t3");
  constexpr auto KwlDebugsetT4              = makeFlashStringLiteral("/t4");

  constexpr auto KwlDebugsetDP1             = makeFlashStringLiteral("/dp1");
  constexpr auto KwlDebugsetDP2             = makeFlashStringLiteral("/dp2");

  // Die folgenden Topics sind nur für die SW-Entwicklung, um Scheduler info auszulesen
  constexpr auto KwlDebugsetSchedulerGetvalues   = makeFlashStringLiteral("/scheduler/getvalues");
  constexpr auto KwlDebugsetSchedulerResetvalues = makeFlashStringLiteral("/scheduler/resetvalues");
  constexpr auto KwlDebugstateScheduler    = makeFlashStringLiteral("/scheduler/");

  // Die folgenden Topics sind nur für die SW-Entwicklung, um Crash info auszulesen
  constexpr auto KwlDebugsetCrashGetvalues = makeFlashStringLiteral("/crash/getvalues");
  constexpr auto KwlDebugsetCrashResetvalues = makeFlashStringLiteral("/crash/resetvalues");
  constexpr auto KwlDebugsetCrashProvoke   = makeFlashStringLiteral("/crash/provoke_IKNOWWHATIMDOING");
  constexpr auto KwlDebugstateCrash        = makeFlashStringLiteral("/crash/");

  // Die folgenden Topics sind nur für die SW-Entwicklung, um NTP zu simulieren.
  constexpr auto KwlDebugsetNTPTime        = makeFlashStringLiteral("/ntp/time");

  // Die folgenden Topics sind nur für die SW-Entwicklung, um Kalibrierung explizit zu setzen
  constexpr auto KwlDebugsetFan1PWM         = makeFlashStringLiteral("/fan1/pwm");
  constexpr auto KwlDebugsetFan2PWM         = makeFlashStringLiteral("/fan2/pwm");
  constexpr auto KwlDebugsetFanPWMStore     = makeFlashStringLiteral("/fan/pwm/store_IKNOWWHATIMDOING");

  // Die folgenden Topics sind nur für die SW-Entwicklung, um Lueftergeschwindigkeit zu simulieren
  // Man kann die PWM->Speed Uebersetzung steuern, default 10 (bis 10000rpm via PWM).
  constexpr auto KwlDebugsetFan1            = makeFlashStringLiteral("/fan1");
  constexpr auto KwlDebugsetFan2            = makeFlashStringLiteral("/fan2");
}
