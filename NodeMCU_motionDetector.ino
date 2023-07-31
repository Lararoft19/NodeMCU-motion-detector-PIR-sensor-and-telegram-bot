#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h> //universal telegram bot library
#include <ArduinoJson.h>
// fill in network credential
const char* ssid = "";
const char* password = "";
// Initialize Telegram BOT
#define BOTtoken "5916133199:AAFFcnjTbLamrv_opdEuqAFcfSKGZMgbpcA" // Bot
Token from Botfather
#define CHAT_ID "1041336604" //chatID from IDBot
X509List cert(TELEGRAM_CERTIFICATE_ROOT); //telegram root cert for esp8266
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
const int motionSensor = 14; // PIR Motion Sensor
const int LEDR = 5; //red led
const int LEDG = 4; //green led
const int buzzer = 13; //buzzer
int delayValue1 = 500;
int delayValue2 = 5000;
bool motionDetected = digitalRead(motionSensor);
// Indicates when motion is detected
void ICACHE_RAM_ATTR detectsMovement() {
//Serial.println("MOTION DETECTED!!!");
motionDetected = true;
}
void setup() {
Serial.begin(115200);
configTime(0, 0, "pool.ntp.org"); //get UTC time via NTP

16

client.setTrustAnchors(&cert); //Add root certificate for
api.telegram.org
// PIR Motion Sensor mode INPUT_PULLUP
pinMode(motionSensor, INPUT_PULLUP);
pinMode(LEDR, OUTPUT);
pinMode(LEDG, OUTPUT);
pinMode(buzzer, OUTPUT);
digitalWrite(LEDG, HIGH);
// Set motionSensor pin as interrupt, assign interrupt function and set
RISING mode
attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement,
RISING);
// Attempting to connect to Wifi network
Serial.print("Connecting Wifi: ");
Serial.println(ssid);
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(500);
}
Serial.println("");
Serial.println("WiFi connected:");
Serial.println(ssid);
Serial.print("IP address: ");
Serial.println(WiFi.localIP());
bot.sendMessage(CHAT_ID, "Bot started up", "");
}
void loop() {
if(motionDetected == true){
bot.sendMessage(CHAT_ID, "Motion detected!!!", "");
Serial.println("Motion Detected!!!");

17

motionDetected = false;
digitalWrite(LEDR, HIGH);
digitalWrite(buzzer, HIGH);
digitalWrite(LEDG, LOW);
delay(delayValue1);
}
delay(delayValue2); //delay 5seconds
digitalWrite(LEDR, LOW);
digitalWrite(buzzer, LOW);
digitalWrite(LEDG, HIGH);
}