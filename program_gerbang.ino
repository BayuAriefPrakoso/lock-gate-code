#include <SPI.h>
#include <MFRC522.h>

#define pb digitalRead(A0)
#define mag digitalRead(A1)

#define bon digitalWrite(8, HIGH)
#define bof digitalWrite(8, LOW)
#define ron digitalWrite(7, HIGH)
#define rof digitalWrite(7, LOW)
#define gon digitalWrite(6, HIGH)
#define gof digitalWrite(6, LOW)
#define lon digitalWrite(5, HIGH)
#define lof digitalWrite(5, LOW)

MFRC522 rfid(10, 9);
MFRC522::MIFARE_Key key;

bool kon = false;
String ID;

char *admin[]{
  "6c3bdf22","434d215","93a015","b3f3315"
};

char *user[]{
  "e3851315","735e1f15","f3ae1e15","77a9ddd7","4315ea14",
  "f36c314","4396f214","23941615","9366b214","d3e2ea14",

  "833aff14","83b9f214","63f6ef14","93e5bb14","d35b2915",
  "c3e3315","73f0f014","93a32215","5318f714","b352eb14",

  "a333815","c33ae614","73a0f114","c34c815","c321ef14",
  "f384e814","334f1315","835a2515","c31ea15","d3cf1415",

  "b39a515","336ec14","8316e15","38b215","533ee814",
  "33ddec14","3741915","e37b1415","a3ade614","37ef114",

  "e392ed14","73ef015","53eb415","b3baf614","3341315",
  "e3bdea14","23191115","a341fd14","a301315","53e1f714",

  "d35b815","63ba1215","d34db15","318f814","13d91d15",
  "a3d2f114","4388eb14","139c1f15","63ad415","b3c0315",

  "d326715","f3bdfe14","539415","43761215","e367615",
  "b3702715","331ea15","9339f214","53f0915","1323f914",
};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);

  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);

  gof; ron; lon;
  delay(2000);
}

void loop(){
  if(mag){
    while(mag){
      bon; delay(25);
      bof; delay(25);
    }
  }
//  Serial.println(mag);

  if(!pb){buka();}

  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  byte block;
  byte len;
  MFRC522::StatusCode status;

  if(!rfid.PICC_IsNewCardPresent()){return;}
  if(!rfid.PICC_ReadCardSerial()){return;}

  read_rfid();
  int x;
  for(int i=0; i<4; i++){
    if(ID == admin[i]){kon = true; x = i;}
  }
  if(kon){Serial.print("admin ");}
  if(!kon){
    for(int i=0; i<70; i++){
      if(ID == user[i]){kon = true; x = i+1;}
    }
    if(kon){Serial.print("user ");}
  }

  if(kon){
    bon;
    delay(10);
    bof;
    Serial.println(x);
//    gon; rof;
//    delay(2000);
    buka();
//    ron; gof;
  }
  else{
    bon;
    delay(10);
    bof;
    delay(100);
    bon;
    delay(10);
    bof;
    Serial.println("bukan");
  }

  kon = false;

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  delay(1000);
}

void read_rfid(){
  ID = "";
  for(byte i = 0; i < rfid.uid.size; i++){
    ID += String(rfid.uid.uidByte[i], HEX);
  }
  Serial.print(ID);
  Serial.print("\t");
}

void buka(){
  gon; rof;
  lof;
  delay(7000);
  lon;
  ron; gof;
  int i = 0;
  while(mag and i < 1200){
    i++;
    delay(100);
//    Serial.println(i);
  }
}
