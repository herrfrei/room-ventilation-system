# Steuerung einer Lüftungsanlage für Wohnhäuser

Diese Steuerung wurde als Ersatz der Originalsteuerung entwickelt.

Das Original war Pluggit P300. Diese Steuerung funktioniert ebenso für Pluggit P450 und viele
weitere Lüftungsanlagen.

Es werden:
1. zwei Lüfter angesteuert und deren Tachosignale ausgelesen
2. vier Temperatursensoren abgefragt
3. Steuerung Abluftventilator zum Frostschutz
4. Optional: Vorheizregister als Frostschutz 
5. Optional: Sommer-Bypass geschaltet
6. Optional: Bis zu zwei Temperatur- und Feuchtigkeitssensore auslesen
7. Optional: Luftqualitätsensor (VOC) und CO2 Sensor auslesen
Die Drehzahlregelung der Lüftermotoren erfolgt durch PID-Regler. Dies sorgt dafür, das die geforderten
Drehzahlen der Lüfter sicher erreicht werden. Die Leistungssteuerung des Vorheizregisters erfolgt
ebenfalls durch einen PID-Regler.

Differenzdrucksensoren werden bisher nicht berücksichtigt.

Die Steuerung ist per LAN (W5100) erreichbar. Als Protokoll wird mqtt verwendet. Über mqtt liefert
die Steuerung Temperaturen, Drehzahlen der Lüfter, Stellung der Bypassklappe, den Status der AntiFreeze
Funktion und sonstige Werte zurück und es können verschiedene Parameter gesetzt werden.

Zusätzlich bietet die Steuerung Unterstützung für TFT Touchscreen, um einerseits die Messwerte
anzuzeigen und andererseits die Steuerung zu konfigurieren. Touchkalibrierung erfolgt bei dem
ersten Touch oder nach langen Touch auf Hauptseite (8 Sekunden). Im Verzeichnis Screenshots
befinden sich ein paar [Screenshots](Screenshots/README.md).

![Main screen](Screenshots/01_main.png)

Im Verzeichnis Docs befindet sich weitere Dokumentation zu verschiedenen Themen.

Um das Projekt zu bauen müssen folgende Voraussetzungen erfüllt sein:
  - Folgende Libraries müssen installiert werden: SPI, EEPROM, PubSubClient,
    Adafruit_GFX_Library, DHT_sensor_library, PID, Adafruit_TouchScreen,
    DallasTemperature, Adafruit_Unified_Sensor, MCUFRIEND_kbv, OneWire,
    Wire, Ethernet
  - Das Projekt bringt eigene Libraries mit. Diese müssen ebenfalls installiert
    werden, am einfachsten als symbolische Links. Der Skript link_libs.sh
    linkt die Libraries an die (hoffentlich) richtige Stelle.

# Anpassungen für unser Gerät (BJ 2006)

- Lüfter sind R3G225-AE19-12 (Nenndrehzahl 2850 U/min)
- Bypass benötigt Spannung auf braun (Pin 4) und weiß (Pin 3) zum Schließen, nur auf braun zum Öffnen
  - Standard ist: Öffnen bei Spannung an Pin 3 (weiß) und Schließen des Bypasses bei Spannung an Pin 4 (braun)
  - SummerBypass.cpp setzt REL3 bei Betrieb immer auf ON und REL4 beim Öffnen auf ON und Schließen auf OFF
