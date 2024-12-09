#define BLYNK_TEMPLATE_ID TMPL2Aqram95T   //Identifiant du template Blynk
#define BLYNK_TEMPLATE_NAME Domotix      //Nom du template Blynk
#define BLYNK_AUTH_TOKEN G_sMr9ge7lSBJO3PH5e2VD3TdUh6X0Ak   //Token d'authentification

#include BlynkSimpleEsp32.h
#include DHT.h

#define DHTPIN 26        //Pin connecté au capteur DHT (GPIO26)
#define DHTTYPE DHT22    //Type du capteur DHT (DHT22 ou DHT11)
#define LEDPIN 4         //Pin connecté à la LED (GPIO4)

 Identifiants Wi-Fi
char ssid[] = Wokwi-GUEST;
char pass[] = ;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);            //Initialisation de la communication série
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);   //Connexion à Blynk avec les identifiants

  dht.begin();                   //Initialisation du capteur DHT
  pinMode(LEDPIN, OUTPUT);       //Configuration de la LED en mode sortie

  Serial.println(Démarrage du système Domotix...);
}

void loop() {
  Blynk.run();                   //Lancer le processus Blynk
  sendSensorData();              //Envoi des données du capteur
}

 Envoi des données de température et d'humidité à Blynk
void sendSensorData() {
  float temp = dht.readTemperature();   //Lecture de la température
  float hum = dht.readHumidity();       //Lecture de l'humidité

  if (isnan(temp)  isnan(hum)) {
    Serial.println(Erreur de lecture du capteur DHT);
    return;
  }

   Envoi des valeurs à Blynk
  Blynk.virtualWrite(V3, temp);   //Température sur V0
  Blynk.virtualWrite(V1, hum);    //Humidité sur V1

   Affichage sur le terminal série
  Serial.print(Température );
  Serial.print(temp);
  Serial.print( °C, Humidité );
  Serial.print(hum);
  Serial.println( %);
}

 Contrôle de la LED via Blynk (associée au bouton V2)
BLYNK_WRITE(V2) {
  int ledState = param.asInt();   //Récupération de l'état (0 ou 1)
  digitalWrite(LEDPIN, ledState);  //Mise à jour de l'état de la LED

  if (ledState == 1) {
    Serial.println(LED allumée via Blynk);
  } else {
    Serial.println(LED éteinte via Blynk);
  }
}
