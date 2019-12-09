import processing.serial.*;
Serial myPort;
int muestras=1;

int[] B1 =  new int [muestras]; //Vectores Auxiliares que van almacenando valores leidos
int[] B2 =  new int [muestras];
int[] B3 =  new int [muestras];
int[] B4 =  new int [muestras];


void setup() {     //Funcion que inicializa el puerto serial y tamaño de ventana
      myPort = new Serial(this, Serial.list()[0],115200);
      size(1200,650);
}

void leer(){ 

  for(int j=0;j<muestras;j++){ 
    if(myPort.available()>0) {
      do
      {B1[j]=myPort.read();
      } while(B1[j] < 0x80); //Se almacena 1 byte en B1 y se modifica hasta que se lee el byte que inicia con 01 o 00, como establece el protocolo
       B2[j]=myPort.read(); // Una vez sincronizada la lectura se procede a almacenar los bytes en el orden que se requiere
       B3[j]=myPort.read();
       B4[j]=myPort.read();
    }
  }
}

void draw (){
  leer();
}
 
