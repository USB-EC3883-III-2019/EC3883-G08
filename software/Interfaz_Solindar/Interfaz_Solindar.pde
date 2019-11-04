import processing.serial.*;
Serial myPort;
int muestras=1;

int[] B1 =  new int [muestras]; //Vectores Auxiliares que van almacenando valores leidos
int[] B2 =  new int [muestras];
int[] B3 =  new int [muestras];
int[] B4 =  new int [muestras];


float[] PO =  new float [muestras];//Vectores que almacenan los datos ya arreglados
int[] SONAR =  new int [muestras];
int[] LIDAR =  new int [muestras];

float[] A1= new float[muestras];
float[] A2= new float[muestras];
float[] A3= new float[muestras];

int[] pixsDistance= new int[muestras];

int[] SONARCM= new int[muestras]; // vectores que almacenan las medidas ya en cm 
int[] LIDARCM= new int[muestras];
int[] FUSION= new int[muestras];
boolean reverse = false;

boolean BFUSION= false;//flags para cada boton
boolean BLIDAR= false;
boolean BSONAR= true;

float x1= 2;
float x2= 5;
float x3= pow((1/x1)+(1/x2),-1);
      
PrintWriter output;

void CrearBotonRect(int x, int y, int ancho, int alto, String texto){//Funcion que crea botones rectangulares
  stroke(#3ED33F);                                                         // Recibe coordenadas de punto superior izquierdo, ancho y alto, y el texto que recibe
  fill(332);
  rect(x,y,ancho, alto);
  fill(#3ED33F);
  textSize(20);
  text(texto,x+30,y+20);
}

boolean BotonRectangular (int xizq, int yizq, int ancho, int alto) { //Funcion que determina si se presiona sobre uno de los botones rectangulares
  if ((mouseX>=xizq) && (mouseX<=xizq+ancho) && (mouseY>=yizq) && (mouseY<=yizq+alto))
    {return true;
  }
  else {
  return false;
  }
}


void setup() {     //Funcion que inicializa el puerto serial y tamaño de ventana
      myPort = new Serial(this, Serial.list()[0],115200);
      myPort.buffer(muestras*4); //tamano del buffer
      size(1200,650);
      output = createWriter("medidas.txt"); 
}



void leer(){ 

  for(int j=0;j<muestras;j++){ 
    if(myPort.available()>0) {
      do
      {B1[j]=myPort.read();
      } while(B1[j] >= 0x80); //Se almacena 1 byte en B1 y se modifica hasta que se lee el byte que inicia con 01 o 00, como establece el protocolo
       B2[j]=myPort.read(); // Una vez sincronizada la lectura se procede a almacenar los bytes en el orden que se requiere
       B3[j]=myPort.read();
       B4[j]=myPort.read();
    }
  }
  
  
    for (int i=0;i<muestras;i++){

      SONAR[i] = (B2[i]&0x7F); //Shifteo el segundo byte cinco veces para obtener el bit digital 1
      
      LIDAR[i] = ((B3[i]&0x1F)<<7)|(B4[i]&0x7F); //Shifteo el tercer byte cinco veces para obtener el bit digital 2
      
      PO[i] = B1[i]&0x3F;
      if((B1[i]>>6)==1){
        reverse = true;
        PO[i]=192-(int(PO[i]*3.5));
        if(PO[i]<0){
          PO[i]=0;
        }
      }
      else{
        reverse=false;
        PO[i]=int(PO[i]*3.5);
        if(PO[i]>180){
          PO[i]=180;
        }
      }
      A1[i]=2000000*pow(LIDAR[i],-1.5);
      LIDARCM[i]=int(A1[i]);
      if(LIDARCM[i]>80){ LIDARCM[i]=80;}
      
      A2[i]=SONAR[i]*61/58;
      SONARCM[i]= int (A2[i]);
      if(SONARCM[i]>80){ SONARCM[i]=80;}
      
      A3[i]=x3*((SONARCM[i]/x1)+(LIDARCM[i]/x2));
      FUSION[i]= int (A3[i]);
      if(FUSION[i]>80){ FUSION[i]=80;}
    }
  
}

void draw (){
    noStroke();
    fill(#B4ABAB);   
    rect(0,600,1200,50);




 fill(98,245,31);
 noStroke();
    fill(0,4);
   rect(0, 0, 1200, 600);
 
   rect(0, 0, 1200, 600);
   noStroke();
   fill(98,245,31); // color gris
  

  
  leer();
  drawRadar();
  drawLine();
  drawObject();
  drawText(); //se llama a la funcion dibujo que contiene mas elementos de la interfaz
 
}

void drawRadar() {
  pushMatrix();
  translate(550,510); // Dibujas las nuevas coordenadas
  noFill();
  strokeWeight(2);
  stroke(98,245,100);

  // dibuja las lineas de arco
  arc(0,0,1000,1000,PI,TWO_PI);
  arc(0,0,900,900,PI,TWO_PI);
  arc(0,0,800,800,PI,TWO_PI);
  arc(0,0,700,700,PI,TWO_PI);
  arc(0,0,600,600,PI,TWO_PI);
  arc(0,0,500,500,PI,TWO_PI);
  arc(0,0,400,400,PI,TWO_PI);
  arc(0,0,300,300,PI,TWO_PI);

  // dibuja las lineas de ángulo
  line(-500,0,500,0);
  line(0,0,-500*cos(radians(30)),-500*sin(radians(30)));
  line(0,0,-500*cos(radians(60)),-500*sin(radians(60)));
  line(0,0,-500*cos(radians(90)),-500*sin(radians(90)));
  line(0,0,-500*cos(radians(120)),-500*sin(radians(120)));
  line(0,0,-500*cos(radians(150)),-500*sin(radians(150)));
  line(0,0,-500*cos(radians(180)),-500*sin(radians(180)));
  line(-500*cos(radians(30)),0,500,0);

  
  popMatrix();
  
  CrearBotonRect(1015,60,120,30, "LIDAR");
  CrearBotonRect(1015,140,120,30, "SONAR");
  CrearBotonRect(1015,220,120,30, "FUSION");
  
  if(BSONAR){
    noFill();    
    rect(1020,140,110,20);

  }
  if(BLIDAR){
     noFill();
     rect(1020,60,110,20);

  }
  if(BFUSION){
   noFill();
    rect(1020,220,110,20);
 
  }
}
void drawObject() {
  pushMatrix();
  translate(550,510); // Mueve las coordenadas a partir de la nueva ubicación
  if(BSONAR){

   for(int i =0; i<muestras; i++){
  strokeWeight(9);
  stroke(255,10,100);
      
      output.println("SONAR: ");
      output.println(SONARCM[i]);
        if(SONARCM[i]<80){ 
          
      pixsDistance[i] = SONARCM[i]*6; 
      point(pixsDistance[i]*cos(radians(PO[i])),-pixsDistance[i]*sin(radians(PO[i])));
      
        }
        else{
          text("SONAR : FUERA DE RANGO", 30, 30);
        }
  }
  }
  if(BLIDAR){
  strokeWeight(9);
  stroke(255,100,10);
    for(int i =0; i<muestras; i++){
      output.println("LIDAR: ");
      output.println(LIDARCM[i]);
      if(LIDARCM[i]<80){ 
      pixsDistance[i] = LIDARCM[i]*6; 
      point(pixsDistance[i]*cos(radians(PO[i])),-pixsDistance[i]*sin(radians(PO[i])));
    }else{
      text("LIDAR  : FUERA DE RANGO", 30, 50);
    }
  }
  }
  if(BFUSION){
  strokeWeight(9);
  stroke(255,10,10);
    for(int i =0; i<muestras; i++){

      output.println("FUSION: ");
      output.println(FUSION[i]);
      if(FUSION[i]<80){
      pixsDistance[i] =FUSION[i]*6;
      point(pixsDistance[i]*cos(radians(PO[i])),-pixsDistance[i]*sin(radians(PO[i])));
      }else{
        text("FUSION : FUERA DE RANGO", 30, 70);
      }
    }
 
  }
  popMatrix();
}



void drawLine() {
 pushMatrix();
  strokeWeight(9);
  stroke(30,250,60);
  translate(550,510); // Mueve las cordenadas a partir de la nueva ubicación
    for(int i =0; i<muestras; i++){
   line(0,0, 500*cos(radians(PO[i])),-500*sin(radians(PO[i]))); // draws the line according to the angle
    }
   popMatrix();
}
void drawText() { // dibuja el texto en la pantalla
 
  pushMatrix();
  //fill(0,0,0);
  stroke(#0F0606);
  //rect(0, 1010, width, 1080);
  //fill(98,245,31);
  textSize(20);
  stroke(#0F0606);
; 
  for(int i =0; i<muestras; i++){
    text("DISTANCIA SONAR  " + SONARCM[i] +" cm", 30, 630);
    text("DISTANCIA LIDAR  " + LIDARCM[i] +" cm", 300, 630);
    text("DISTANCIA FUSION  " + FUSION[i] +" cm", 600, 630);
    text("POSICION  " + PO[i] +"°", 900, 630);
   }
  popMatrix();
}


void mousePressed (){//Funcion que define la accion a realizar si se presiona el mouse
  if (BotonRectangular (1015,140,120,30)) { //Define las condiciones para la cual se activa cierto boton
    if (BSONAR){ //Si el boton ya estaba activado no hace nada
      BSONAR=false;
    }
    else{
      BSONAR=true;

    }
  }
  else if (BotonRectangular (1015,60,120,30) ){ 
    if (BLIDAR){
      BLIDAR=false;
    }
    else{
  
      BLIDAR=true;

    }
  }
  else if (BotonRectangular (1015,220,120,30)){
    if (BFUSION){
    BFUSION=false;
    }
    else{
  
      BFUSION=true;

    }
  }
}
