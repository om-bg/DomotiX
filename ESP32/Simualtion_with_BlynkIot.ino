#include <WiFi.h>
#include <FirebaseESP32.h>

// Configuration Wi-Fi
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""

// Configuration Firebase
#define FIREBASE_HOST "https://domotix-41318-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "92PiYgqHGLhoTj3siw0s3tkstjUMoSmxfz4fmiRZ" // Remplacez par votre Database Secret

FirebaseConfig config;
FirebaseAuth auth;

// Pin de la LED
#define LED_PIN 4

FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);

  // Connexion Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connexion au WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnecté au WiFi");

  // Configuration Firebase
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  // Initialisation Firebase
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Configuration de la LED
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Lecture du statut de la LED dans Firebase
  if (Firebase.getString(firebaseData, "/LED_Status")) {  // Utilisation de Firebase.getString
    String ledStatus = firebaseData.stringData();
    Serial.println("Statut LED : " + ledStatus);

    if (ledStatus == "ON") {
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }
  } else {
    Serial.println("Erreur Firebase : " + firebaseData.errorReason());
  }

  delay(1000);
}
