#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";          // Remplacez par votre SSID Wi-Fi
const char* password = ""; // Remplacez par votre mot de passe Wi-Fi

const char* firebaseHost = "https://domotix-41318-default-rtdb.firebaseio.com"; // URL de Firebase
const char* apiKey = "92PiYgqHGLhoTj3siw0s3tkstjUMoSmxfz4fmiRZ"; // Clé API Firebase


const int ledPin = 4; // GPIO où la LED est connectée

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.begin(ssid, password);

  // Connexion au Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au Wi-Fi...");
  }
  Serial.println("Connecté au Wi-Fi !");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // URL de la branche simple dans Firebase
    String url = String(firebaseHost) + "/LED.json?auth=" + apiKey;

    http.begin(url.c_str());
    int httpResponseCode = http.GET(); // Effectue une requête GET pour lire l'état de la branche

    if (httpResponseCode > 0) {
      String payload = http.getString();
      payload.trim(); // Supprime les espaces inutiles

      Serial.println("État reçu de Firebase : " + payload);

      if (payload == "\"ON\"") { // Firebase renvoie "ON" avec des guillemets
        digitalWrite(ledPin, HIGH); // Allume la LED
        Serial.println("LED allumée !");
      } else if (payload == "\"OFF\"") {
        digitalWrite(ledPin, LOW); // Éteint la LED
        Serial.println("LED éteinte !");
      } else {
        Serial.println("Valeur inattendue !");
      }
    } else {
      Serial.print("Erreur HTTP : ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Wi-Fi déconnecté !");
  }

  delay(2000); // Vérifie l'état toutes les 2 secondes
}
