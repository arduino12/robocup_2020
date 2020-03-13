/*
 * Moves the robot legs by the Pixy2 object positions.
 * 
 * Arad Eizen 13/03/2020.
 */
#ifndef _OTA_H_
#define _OTA_H_

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#define WIFI_SSID						"....."
#define WIFI_PASS						"....."
#define OTH_HOSTNAME					"robocup2020"
// #define OTH_PASSWORD					"asm"
#define OTA_LOOP_MS						(100)

void ota_begin()
{
	WiFi.mode(WIFI_STA);
	WiFi.begin(WIFI_SSID, WIFI_PASS);
	while (WiFi.waitForConnectResult() != WL_CONNECTED) {
		Serial.println("WiFi connection failed! No OTA...");
		return;
	}
	Serial.printf("WiFi connected!\t\t%s.local (%s)\n", OTH_HOSTNAME, WiFi.localIP().toString().c_str());

	ArduinoOTA.setHostname(OTH_HOSTNAME);
#if defined(OTH_PASSWORD)
	ArduinoOTA.setPassword(OTH_PASSWORD);
#endif
	ArduinoOTA.begin();
}

void ota_loop()
{
	static uint32_t last_ms = 0;
	uint32_t cur_ms = millis();

	/* run our loop every OTA_LOOP_MS milliseconds */
	if ((cur_ms - last_ms) < OTA_LOOP_MS)
		return;
	last_ms = cur_ms;

	ArduinoOTA.handle();
}

#endif
