#include <PS2X_lib.h>  //for v1.6
#include <SoftwareSerial.h>

SoftwareSerial ss(3, 2); // RX, TX //Pin SoftwareSerial

byte start, select, up, down, right, left, kotak, segitiga, bulat, x, r1, r2, l1, l2, r3, l3 ;
int ly, lx, ry, rx ;
int valLX, valLY, valRX, valRY;
byte rAtas, rBawah, rKanan, rKiri;
byte lAtas, lBawah, lKanan, lKiri; 
char output[25];
const int buzPin = 9 ;
//#define PS2_DAT        12  //14    
//#define PS2_CMD        11  //15
//#define PS2_SEL        10  //16
//#define PS2_CLK        13  //17

//#define pressures   false
//#define rumble      false

PS2X ps2x; 

byte error = 0;

void setup(){
  Serial.begin(57600);
  ss.begin(9600);
  delay(300);     
  error = ps2x.config_gamepad(13, 11, 10, 12, 0, 0);
  pinMode(buzPin,OUTPUT);
  
  if(error == 0){
  digitalWrite(buzPin,1);
  delay(300);
  digitalWrite(buzPin,0);
  delay(300);
  digitalWrite(buzPin,1);
  delay(600);
  digitalWrite(buzPin,0);
  }  
  else {
    digitalWrite(buzPin,1);
  }
}

void loop() {
  psRead();
  delay(80);
}

void psRead() {
  ps2x.read_gamepad(false, 0); 
	
	if(ps2x.Button(PSB_PAD_UP)) 	{	up       = 1; }else up       	= 0; 
  if(ps2x.Button(PSB_PAD_DOWN))	{ down     = 1; }else down     	= 0;
  if(ps2x.Button(PSB_PAD_RIGHT)){ right    = 1; }else right    	= 0;
  if(ps2x.Button(PSB_PAD_LEFT))	{ left     = 1; }else left     	= 0;
	
	if(ps2x.Button(PSB_TRIANGLE))	{ segitiga = 1; }else segitiga 	= 0;
  if(ps2x.Button(PSB_CROSS))		{ x        = 1; }else x        	= 0;
	if(ps2x.Button(PSB_SQUARE))		{ kotak    = 1; }else kotak    	= 0;
  if(ps2x.Button(PSB_CIRCLE))		{ bulat    = 1; }else bulat    	= 0;

	if(ps2x.Button(PSB_R1))				{ r1       = 1; }else r1     		= 0;
  if(ps2x.Button(PSB_R2))				{ r2       = 1;	}else r2     		= 0;
	if(ps2x.Button(PSB_R3))				{ r3       = 1; }else r3     		= 0;
	if(ps2x.Button(PSB_L1))				{ l1       = 1;	}else l1     		= 0;
  if(ps2x.Button(PSB_L2))				{ l2       = 1; }else l2     		= 0;
	if(ps2x.Button(PSB_L3))				{ l3       = 1; }else l3     		= 0;
	if(ps2x.Button(PSB_SELECT))		{ select   = 1; }else select   	= 0; 
	if(ps2x.Button(PSB_START))		{ start    = 1; }else start    	= 0;
    
	valRX = ps2x.Analog(PSS_RX);
  valRY = ps2x.Analog(PSS_RY);
  valLX = ps2x.Analog(PSS_LX);
  valLY = ps2x.Analog(PSS_LY); 
	
//	byte rAtas, rBawah, rKanan, rKiri;
////////============Analog Kanan Vertical==================//////////
  
	if(valRY > 128 + 3 ){
		rBawah = 1;
	}
	else if(valRY < 128 - 3){
		rAtas = 1;
	}
	else if (valRY > (128 - 3) && valRY < 128 + 3 ){
		rAtas  = 0;
		rBawah = 0;
	}
/////++++++++++++++++++++++++++++++++++++++++++++++++/////////

//////=============Analog Kanan Horizontal=========///////////
  
  if(valRX > 128 + 3 ){
    rKanan = 1;
  }
  else if(valRX < 128 - 3){
    rKiri = 1;
  }
  else if (valRX > (128 - 3) && valRX < 128 + 3 ){
    rKanan  = 0;
    rKiri = 0;
  }

////////////++++++++++++++++++++++++++++++++++++++++++///////

/////////=============Analog Kiri Vertical============/////////////
  
  if(valLY > 128 + 3 ){
    lBawah = 1;
  }
  else if(valLY < 128 - 3){
    lAtas = 1;
  }
  else if (valLY > (128 - 3) && valLY < 128 + 3 ){
    lAtas  = 0;
    lBawah = 0;
  }

/////////++++++++++++++++++++++++++++++++++++++++++++++/////////
///////////==========Analog Kiri Horizontal====================////////
  
  if(valLX > 128 + 3 ){
    lKanan = 1;
  }
  else if(valLX < 128 - 3){
    lKiri = 1;
  }
  else if (valLX > (128 - 3) && valLX < 128 + 3 ){
    lKanan  = 0;
    lKiri = 0;
  }

///////konversi data to Desimal////
int aa;
int bb; 
int cc;
aa = (128*up)+(64*right)+(32*down)+(16*left)+(8*segitiga)+(4*bulat)+(2*x)+(1*kotak);
bb = (128*r1)+(64*r2)+(32*l1)+(16*l2)+(8*select)+(4*start)+(2*l3)+(1*r3);
cc = (128*lAtas)+(64*lKanan)+(32*lBawah)+(16*lKiri)+(8*rAtas)+(4*rKanan)+(2*rBawah)+(1*rKiri);

//menghitung Digit//
//int angkaA = aa,angkaB =bb,angkaC = cc;
//int banyakDigitA = 0 ;
//int banyakDigitB = 0 ;
//int banyakDigitC = 0 ; 
//while(angkaA >0 ||angkaB >0 ||angkaC >0 ){
//   angkaA = (angkaA - (angkaA%10))/10;
//   angkaB = (angkaB - (angkaB%10))/10;
//   angkaC = (angkaC - (angkaC%10))/10;
//  banyakDigitA++ ;
//  banyakDigitB++ ;
//  banyakDigitC++ ;
//}


  
//    sprintf(output,"#,%03d,%03d,%03d\n",aa,bb,cc);
    sprintf(output,"*%03d,%03d,%03d#\n",aa,bb,cc);
     ss.print(output);
     Serial.print(output);

}
