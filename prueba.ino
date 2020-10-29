int trigPin = 7;  //Definimos los pines con los que trabajaremos
int echoPin = 8;
int LEDR = 5;
int LEDV = 6;
int LEDA = 4;
int BOMBA = 2;
float velocidad = 0.0343;  //velocidad del sonido en cm/us
long duracion, distancia ;

void setup()
{                                                                                                                           
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);   
  pinMode(LEDR, OUTPUT);   
  pinMode(LEDV, OUTPUT);
  pinMode(LEDA, OUTPUT);
  pinMode(BOMBA, OUTPUT);
  digitalWrite (LEDR , LOW);  
  digitalWrite (LEDV , LOW);  
  digitalWrite (LEDA , LOW);  
}
void loop()
  {   
    if (cerca()){
      digitalWrite (LEDV , HIGH);     //Si el sensor detecta una distancia menor a 20 cm enciende el LED Rojo
      digitalWrite (LEDR , LOW);      // y apaga el verde
      delay(2000);
      if(cerca()){
        digitalWrite (LEDA , HIGH);
        digitalWrite (BOMBA , HIGH);  
        Serial.println("1");
        delay(200);
        digitalWrite (LEDA , LOW); 
        digitalWrite (BOMBA , LOW); 
        //Serial.println("2");
        //delay(3000);
      }
    }
    else{       // de lo contrario
      digitalWrite (LEDV , LOW);    //apaga el rojo
      digitalWrite (LEDR , HIGH);   //enciende el verde
      }
  }

boolean cerca(){
    digitalWrite(trigPin, LOW);        // Nos aseguramos de que el trigger está desactivado
    delayMicroseconds(2);              // Para asegurarnos de que el trigger está LOW
    digitalWrite(trigPin, HIGH);       // Activamos el pulso de salida
    delayMicroseconds(10);             // Esperamos 10µs. El pulso sigue active este tiempo
    digitalWrite(trigPin, LOW);        // Cortamos el pulso y a esperar el ECHO
    duracion = pulseIn(echoPin, HIGH) ; //pulseIn mide el tiempo que pasa entre que el pin declarado (echoPin) cambia de estado bajo a alto (de 0 a 1)
    distancia = velocidad* duracion / 2;   //Dividimos entre 2 porque queremos coger el tiempo de ida (y no ida y vuelta)
    if ( distancia < 10){
      return true;
    }
    else{
      return false;
    }
}
