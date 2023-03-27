#include <WiFi.h>
#include <TimeLib.h>

int sensor =13;
int humedad=0;
int humedadPar=0;
time_t fechas;

/*parametros para enviar*/
int humedadAn=0;
int humedadDe=0;
String idRiego="";
/* SOLO 3 PARAMETROS*/

/*HACER LA CONECCION*/
const char* ssid     = "LAPTOP-QM4PCO1B 9891";
const char* password = "mayito2512";
const char* host = "localhost";
const int port = 80; 

/* Hasta AQUI */

void setup() {
Serial.begin(115200);
   WiFi.mode(WIFI_OFF);
  pinMode(22, OUTPUT);
  pinMode(sensor, INPUT);
   setTime(06,50,0,26,04,2023);
   fechas=now();
}


void loop() {


  
  humedad = analogRead(sensor);
  humedadPar=map(humedad, 1100,4090 , 100,0); // adjust soil level here
  
    Serial.print("-----------------Humedad: ");
    Serial.println(humedadPar);   
  
  if (humedadPar>=10 && humedadPar <=50){
   
    humedadAn=humedadPar;
    
    /*RIEGO*/
    while(humedadPar<50){
      int humedadWHILE = analogRead(sensor);
      int humedadParWHILE=map(humedadWHILE, 1100,4090 , 100,0); // adjust soil level here
      Serial.println("------------------SIGO DENTRO------------------- ");
      digitalWrite(22, HIGH);  
      delay(500);
      if(humedadParWHILE>=50){
        
          Serial.println("CAMBIE DE UNA VEZ POR TODAS");
          humedadDe=humedadParWHILE;
          Serial.print("HUMEDAD DESPUES DE REGAR ");
          Serial.println(humedadDe);  
        }
        digitalWrite(22, LOW);
        humedadPar=humedadParWHILE;
        idRiego=dimeFecha();
    }    
    conexion();   
    WiFi.mode(WIFI_OFF);       
  }
  else{
    digitalWrite(22, LOW);
  }
      Serial.println("-----------------------------------------------------");
      Serial.print("HUMEDAD ANTES DE REGAR ");
      Serial.println(humedadAn);
      Serial.print("HUMEDAD DESPUES DE REGAR ");
      Serial.println(humedadDe); 
      Serial.print("FECHA DEL RIEGO ");
      Serial.println(idRiego); 
      Serial.println("-----------------------------------------------------");
  delay(2000);  




                
}







void conexion(){
  WiFi.mode(WIFI_OFF);
 Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());


  
// Crear una instancia de WiFiClient de http
  WiFiClient client;

  // Conectar a la API
  if (!client.connect("192.168.137.220", 80)) {
    Serial.println("Error de conexión");
    return;
  }
  


 // Enviar los datos a la API
 client.print(String("POST http://192.168.137.220/data") + 
                          ("/") + humedadAn +
                          ("/") + humedadDe +
                          ("/")+ idRiego +
                          " HTTP/1.1\r\n" +
                 "Host: " + "192.168.137.220" + "\r\n" +
                 "Connection: close\r\n\r\n");

                 
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

  // Esperar a que llegue la respuesta de la API
  while (!client.available()) {
    delay(1);
  }

  // Leer la respuesta de la API
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  // Cerrar la conexión
  client.stop();
  WiFi.mode(WIFI_OFF);
}

String dimeFecha(){
char fecha[20];
  int dia = day(fechas);
  int mes = month(fechas);
  int anio = year(fechas);
  sprintf( fecha, "%.2d.%.2d.%.4d", dia, mes, anio);
  return String( fecha );
}
