#include <NimBLEDevice.h>

const char* targetDeviceMACAddress = "08:14:13:08:6c:67"; // Different for each device, use a Bluetooth scanner to find yours
#define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
NimBLERemoteCharacteristic* pRemoteCharacteristic;

void setup() {
  Serial.begin(115200);

  Serial.println("Connecting to lights via bluetooth...");
  NimBLEDevice::init("");
  NimBLEAddress targetAddress(targetDeviceMACAddress);
  NimBLEClient* pClient = NimBLEDevice::createClient();
  if (pClient->connect(targetAddress)) {
    Serial.println("Connected successfully!");
    NimBLERemoteService* pRemoteService = pClient->getService(SERVICE_UUID);
    if (pRemoteService == nullptr) {
      Serial.println("Failed to find service.");
      return;
    }

    pRemoteCharacteristic = pRemoteService->getCharacteristic(CHARACTERISTIC_UUID);
    if (pRemoteCharacteristic == nullptr) {
      Serial.println("Failed to find characteristic.");
      return;
    }

  } else {
    Serial.println("Failed to connect to target device.");
  }

  // Turn off
  uint8_t toggleOff[] = {0x5a, 0x01, 0x02, 0x00};
  pRemoteCharacteristic->writeValue(toggleOff, sizeof(toggleOff), false);
  delay(1000);

  // Turn on
  uint8_t toggleOn[] = {0x5a, 0x01, 0x02, 0x01};
  pRemoteCharacteristic->writeValue(toggleOn, sizeof(toggleOn), false);
  delay(1000);
}

void loop() {
  // Change colour to red
  uint8_t redColourData[] = {0x5a, 0x07, 0x01, 0xFF, 0x00, 0x00};
  pRemoteCharacteristic->writeValue(redColourData, sizeof(redColourData), false);
  delay(500);

  // Change colour to green
  uint8_t greenColourData[] = {0x5a, 0x07, 0x01, 0x00, 0xFF, 0x00};
  pRemoteCharacteristic->writeValue(greenColourData, sizeof(greenColourData), false);
  delay(500);

  // Change colour to blue
  uint8_t blueColourData[] = {0x5a, 0x07, 0x01, 0x00, 0x00, 0xFF};
  pRemoteCharacteristic->writeValue(blueColourData, sizeof(blueColourData), false);
  delay(500);
}
