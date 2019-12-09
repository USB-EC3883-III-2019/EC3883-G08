import processing.serial.*;
Serial myPort;
int muestras=4;
char m, zm, z1, z2, z3, z4, t;
char s=1;
int B1,B2,B3,B4;
int M;

int[] Byte1 =  new int [muestras]; //Vectores Auxiliares que van almacenando valores leidos
int[] Byte2 =  new int [muestras];
int[] Byte3 =  new int [muestras];
int[] Byte4 =  new int [muestras];


void leer(){
    for(int j=0;j<muestras;j++){ //Ciclo quelee los datos del mismo y los almacena en los vectores de lectura
    if(myPort.available()>0) {
      do
      {Byte1[j]=myPort.read();
      } while(Byte1[j] <= 0x80); //Se almacena 1 byte en Byte1 y se modifica hasta que se lee el byte que inicia con 10, como establece el protocolo
       Byte2[j]=myPort.read(); // Una vez sincronizada la lectura se procede a almacenar los bytes en el orden que se requiere
       Byte3[j]=myPort.read();
       Byte4[j]=myPort.read();
    }
  }
   for (int i=0;i<muestras;i++){

     M=((Byte1[i]&0xF)<<4)|(Byte2[i]&0xF); //desentrama el mensaje recibido
   }
   if(M==0){
   }
   else{
      text(" "+M, 80, 290); //imprime el mensaje recibido
   }
}

void setup() {   
  
  myPort = new Serial(this, Serial.list()[2],115200);
  myPort.buffer(muestras); //tamano del buffer
  printArray(Serial.list());
  size(600,500);
  background(0);
}

void draw (){
  
  fill(255);
  textSize(20);
    
switch (s){
 
case 0:
     if(keyCode==ALT){  //en este caso reinicia el juego
      s=1;
      }
   break;
  
case 1:
  background(0);
  text("Seleccione el modo: M (Maestro)/ E (Esclavo)",40, 130);  //inicio del juego, SELECCIONA EL MODO
       if(key== 'M'| key=='m'){    
          s=2;
        }
        
        if(key== 'E'| key=='e'){
          s=3;
        }
          
  break;
  
case 2:
      fill(255);
      background(0);
      text("MODO MASTER ACTIVO: ", 100, 130);  //caso 2 inicia MODO MASTER
      s=4;
      break;
      
case 3:
      background(0);
      fill(255);
      text("MODO ESCLAVO ACTIVO: ", 100, 130); // caso 3 inicia MOOD esclavo y pide el numero de torre
      if(keyCode==ENTER){
      text("Numero de Torre: ", 40, 180);
      s=5;
      }
      break;

case 5:  //envia la flag de que esta en esclavo y del numero de torre al micro
  if(keyPressed){
    if(key==49){ //si es la torre 1 envia como flag 10010000 y 3 bytes de cero
        t=key;
        text(" "+t, 220, 180);
        
         myPort.write(10010000);
         myPort.write(0);
         myPort.write(0);
         myPort.write(0);
         s=7;
       
        
    }
       else  if(key==50){  // si es torre 2 enviaz 10100000 y 3 byte de ceros
        t=key;
        text(" "+t, 220, 180);
         myPort.write(10100000);
         myPort.write(0);
         myPort.write(0);
         myPort.write(0);
         s=7;
    } 
        else if(key==51){  // si es torre 3 enviaz 10110000 y 3 byte de ceros
        t=key;
        text(" "+t, 220, 180);
         myPort.write(10110000);
         myPort.write(0);
         myPort.write(0);
         myPort.write(0);
         s=7;
        
    }
    
       else if(key==52){  // si es torre 4 enviaz 11000000 y 3 byte de ceros
        t=key;
        text(" "+t, 220, 180);
         myPort.write(11000000);
         myPort.write(0);
         myPort.write(0);
         myPort.write(0);
         s=7;
       }
        else { // si se introduce un numero de torre invalido vuelve a este mismo caso, es decir, no hara nada hasta que se introduzca un numero de torre 1, 2, 3 o 4.
        s=5;
      }
  }
  break;
  
case 7:
   text("Presione ENTER para recibir", 40, 400); 
   myPort.write(128|((t&7)<<4)); // sigue enviando la flag del numero de torre hasta que se precione ENTER y empiece a recibir
   myPort.write(0);
   myPort.write(0);
   myPort.write(0);
    if (keyCode==ENTER){
   s=9;}

      break;
      
case 9:
  if(keyCode==ENTER){
    background(0);
    text("MODO ESCLAVO ACTIVO: ", 100, 130);
    text("Numero de Torre: "+t, 40, 180);
    text("Mensaje Recibido: ", 80, 240); //muestra el mensaje recibido
   leer();
  text("Presione ALT para volver a incio", 40, 400); //reinicia el juego si se preciona ALT
  s=0;
  }
  break;


case 4:
      if(keyCode==ENTER){
      text("Escribe mensaje: ", 40, 180);  //MODO master pide el mensaje
      s=6;
      }
      break;
      
case 6:
      if(keyPressed){  
        m=key;
        text("  "+m, 200, 180); // escribe el mensaje
        s=8;
      }
      break;
      
case 8:      
      if(keyCode==ENTER){
      text("Zona M: ", 40, 220); // pide zona por la que va a enviar el master
      s=10;
      }
      break;
      
case 10:
      if(keyPressed){  //escribe la zona del master solo si se introduce una zona valida, es decir, 1, 2, 3, 4, 5, o 6.
          if((key==49)|(key==50)|(key==51)|key==52|(key==53)|(key==54)){ 
            zm=key;
            text("  "+zm, 120, 220);
            s=12;
         } else {s=11;} //si no se introduce una zona correcta vuelve al ciclo 10
      }
     break;
      
case 11:
    if(keyPressed){ 
    s=10;  //vuelve al ciclo 10 si no se introduce la zona correcta
    }
    break;
      
case 12:
      if(keyCode==ENTER){
      text("Zona 1: ", 40, 260); //pide zona de la torre 1
      s=14;
      }
      break;
 
case 14:
      if(keyPressed){
         if(key==48){ // si la zona 1 es cero implica que no hay mas torres ademas de la del master, por lo que automaticamete establece las demas zonas en cero
            z1=key;
            text("  "+z1, 120, 360);
            text("Zona 2:   0", 40, 300);
            text("Zona 3:   0", 40, 340);
            text("Zona 4:   0", 40, 380);
            z2=0;
            z3=0;
            z4=0;
            s=27;
        }
          else if((key==49)|(key==50)|(key==51)|key==52|(key==53)|(key==54)){  // si zona 1 es valida, es decir, es 1, 2, 3, 4, 5 o 6, escribe la zona introducida
            z1=key;
            text("  "+z1, 120, 260);
            s=16;
         } else {s=14;} // repite este caso hasta que se teclee una zona valida.  
      }
     break;

case 16:
      if(keyCode==ENTER){
      text("Zona 2: ", 40, 300); //pide zona 2
      s=18;
      }
      break;
 
case 18:
      if(keyPressed){ 
        if(key==48){ //si la zona 2 es 0, implica que no hay ni torre 2, 3 ni 4, por lo q ecribe todas estas torres en 0
          z2=key;
          text("  "+z2, 120, 300);
          text("Zona 3:   0", 40, 340);
          text("Zona 4:   0", 40, 380);
            z3=0;
            z4=0;
            s=27;
        }
        else if((key==49)|(key==50)|(key==51)|key==52|(key==53)|(key==54)|(key==54)){ //si la zona 2 es 1, 2, 3, 4, 5, o 6, escribe la zona 2
          z2=key;
          text("  "+z2, 120, 300);
          s=20;
          } else {s=18;} // repite este caso hasta que se teclee una zona valida.   
      }
     break;
     
     
case 20:
      if(keyCode==ENTER){
        
        text("Zona 3: ", 40, 340); //pide zona 3
      s=22;
      }
      break;
 
case 22:
      if(keyPressed){  
        if(key==48){ //si la zona 3 es 0, implica que no hay ni torre 3 ni 4, por lo que las establece en cero ambas
        z3=key;
        text("  "+z3, 120, 340);
        text("Zona 4:   0", 40, 380);
            z4=0;
            s=27;
        }
        else if((key==49)|(key==50)|(key==51)|key==52|(key==53)|(key==54)|(key==54)){  //si la zona 3 es un numero valido, escribe la zona
        z3=key;
        text("  "+z3, 120, 340);
        s=24;
        } else {s=22;} // repite este caso hasta que se teclee una zona valida.  
      }
     break;
     

case 24:
      if(keyCode==ENTER){
      text("Zona 4: ", 40, 380); //pide zona 4
      s=26;
      }
      break;
 
case 26:
    
      if(keyPressed){  
        if((key==48)|(key==49)|(key==50)|(key==51)|key==52|(key==53)|(key==54)|(key==54)){ // si la zona es 0, 1, 2, 3, 4, 5 o 6  escribe la zona y sigue
        z4=key;
        text("  "+z4, 120, 380);
        s=27;
        } else {s=26;}  //no hace nada hasta que se teclee una zona valida
      }
     break;

    
case 27:
    text("Presione ENTER para enviar", 40, 420); //indica al usuario que hacer para empezar a enviar
    s=28;
    break;

case 28:
   if(keyCode==ENTER){
   background(0);
   text("MODO MASTER ACTIVO: ", 100, 130); 
   text("enviando... ", 40, 180); 
   B1=(m>>4)|0x80;  //entrama la data 
   B2=((m)& 0xF)|((zm&0xF)<<4);
   B3=((z4&0xF)<<3)|(z3&0xF);
   B4=((z2&0xF)<<3)|(z1&0xF);
   text("byte1: "+binary(B1), 40, 220);  //imprime en la ventana los bytes que se enviaran
   text("byte2: "+binary(B2), 40, 260); 
   text("byte3: "+binary(B3), 40, 300); 
   text("byte4: "+binary(B4), 40, 340);
   myPort.write(B1); //envia los bytes
   myPort.write(B2);
   myPort.write(B3);
   myPort.write(B4);
   s=29;
   }
   break;

   case 29:
   text("Presione SHIFT para recibir", 40, 400);
   myPort.write(B1); //sigue enviando la data hasta q el usuario presione SHIFT para esperar el mensaje que recibira
   myPort.write(B2);
   myPort.write(B3);
   myPort.write(B4);
    if (keyCode==SHIFT){
   s=30;}
   break;
   
case 30:

   if(keyCode==SHIFT){
     background(0); 
     myPort.write(10000000); //envia una flag al micro para indicarle que el master esta listo pare recibir
     myPort.write(0);
     myPort.write(0);
     myPort.write(0);
     text("MODO MASTER ACTIVO: ", 100, 130);
     text("recibiendo... ", 40, 180); 
     leer();  //lee lo que recibio y lo escribe
     text("Mensaje: ", 80, 240); 
     text("Presione ALT para volver a incio", 40, 400);  //indica al usario como reinciar el juego
    
   }
     if(keyCode==ALT){
     s=0;  // una vez que se teclee ALT vuelve al inicio
     }
  break;
}

}
