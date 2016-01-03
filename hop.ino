int cont=0;  //counters you will be using in future
int contador=0;
char basura;  // characters that you don't need
int cont2=0;
String dato="";  //String that will be printed with GPS data
#define SerialGPS Serial2 // Serial2 is the way to communicate to your LISA board
void setup() {
  pinMode(D01, INPUT_PULLUP);
  pinMode(D02, INPUT_PULLUP);
  SerialUSB.begin(9600); //Monitor your board through a terminal on your PC
  Serial2.begin(9600);  //Serial dedicated to the only use of the GPS (receiving data)
  SerialCloud.begin(115200);
 
  
  
  
  bool listo = false; //condition statement to probe that your connection is ready to use
  char char1;   //characters that will help you know when you're ready to go
  char char2;
  char char3;
  
  while (!listo){ // you start your program when your board has already finished it's set up
    if (SerialCloud.available()){ // check if the cloufd data is available
       char1=(char)SerialCloud.read();  // get the first character received from the cloud to know when you're ready
      SerialUSB.write(char1); // Print on your screen that same character so you know what it is
      if (char1=='+'){  //When you see "+++" on your monitor is because you're ready to start using your LISA board
        char2=(char)SerialCloud.read();
        if (char2=='+'){
          char3=(char)SerialCloud.read();
          if (char3== '+'){   // Check in the cloud if the pattern you're looking for actually appears
            listo=true;
          }
        }
        
      }
      
    }
  }
  SerialUSB.write("+++!");


}

void loop() {
  int iread;
  int iread2;
  bool listo;
  char char1;
  char char2;
  char char3;

  iread2=digitalRead(D02);
  
  if (iread2==0){
    listo=false;
    while(!listo){
        if (SerialGPS.available()){
        char1=SerialGPS.read();
        if (char1=='$'){
          char2='d';
          while(char2!='$'){
            char2=SerialGPS.read();
            SerialCloud.write(char2);
            SerialUSB.write(char2);
          }
          listo=true;
        }
      }
    }
    while(iread2==0){
      iread2=digitalRead(D02);
    }
  }
 
  iread=digitalRead(D01);
  if (iread==0){
    listo=false;
    if (SerialGPS.available()){ // check if your GPS is already sending data
      while(!listo){
        char1=(char)SerialGPS.read(); 
        if (char1=='$'){
          char2='d';
          while(char2!='$'){
            if (SerialGPS.available()){
              char2=(char)SerialGPS.read();
              if (char2=='L'){
                cont=cont+1;
                if(cont==2){
                  basura=SerialGPS.read();
                  
                  while(contador<8){
                    char3=(char)SerialGPS.read();
                    dato += char3;
                    contador=contador+1;
                  }
                  
                  while(contador>=8 && contador<13){
                    char3=SerialGPS.read();
                    contador=contador+1;
                  }
                  dato += ",-";
                  SerialUSB.write(contador);
                  while(contador>=13 && contador <23){
                    char3=(char)SerialGPS.read();
                    dato += char3;
                    contador=contador+1;
                  }
                  SerialUSB.println(dato);
                  SerialUSB.println("");
                  SerialCloud.println(dato);
                  dato="";
                  cont=0;
                  contador=0;
                }
                
              }
            }
          }
          listo=true;
          delay(1000);
        }
      }
  }
  }
}
