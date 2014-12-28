
#define LEDPIN 13
#define IRPIN 8
#define __PINA 2
#define __PINB 3
#define __PINC 4


 // ---------------------------------------------------------------------
 // Samsung IR class
 // ---------------------------------------------------------------------
 
 class Samsung
 {
   private:
   // Send a 36kHz-modulated pulse
   static void Pulse(void)
   {
     byte i;
     for (i=0; i<21; i++)
     {
       digitalWrite(IRPIN, HIGH);
       delayMicroseconds(10); // Value adjusted with oscilloscope
       digitalWrite(IRPIN, LOW);
       delayMicroseconds(10); // Value adjusted with oscilloscope
     }
   }
   // Send a bit
   static void SendIRBit(byte b)
   {
     Pulse(); 
     if (b) 
       delayMicroseconds(1390);
     else
       delayMicroseconds(430);
   }
   // Send 4 bits
   static void SendIRNibble(byte b)
   {
     byte i;
     for (i=0; i<4; i++)
       SendIRBit((b>>i)&1);
   }
   // Send a byte
   static void SendIRByte(byte b)
   {
     byte i;
     for (i=0; i<8; i++)
       SendIRBit((b>>i)&1);
   }
 
   public:
   // Send an IR command
   // Type is 0 for TV, 1 for BD
   // Device is 0x0707 for TV, 0x301A for BD
   // Crc should be ~Command, except for tests
   static void SendCommand(char Type, unsigned int Device, unsigned int Command, unsigned char Crc)
   {
     byte i;
    
     // Disable interrupts
     cli();
   
     // Start bit
     for (i=0; i<8; i++)	Pulse();
     delayMicroseconds(4500);
 
     // Send Device Id
     SendIRByte(Device>>8);
     SendIRByte(Device&0xff);
 
     // BD Player
     if (Type==1)
     {
       // Stop bit
       Pulse();
       delayMicroseconds(4500);
       // Send Data
       SendIRNibble(Command>>8);
     }
     
     SendIRByte(Command);
     SendIRByte(Crc);
 
     // Stop bit
     Pulse();
     delayMicroseconds(4500);
   
     // Re-enable interrupts
     sei();
   }
  
   static boolean bEeprom2ByteAddress;
 };
 boolean Samsung::bEeprom2ByteAddress=true;
 

// ---------------------------------------------------------------------
 // Initialization
 // ---------------------------------------------------------------------
 
void setup()
{

 
   // IR Led
   pinMode(IRPIN, OUTPUT);
   digitalWrite(IRPIN, HIGH);

	// led pin
   pinMode(LEDPIN, OUTPUT);
   digitalWrite(LEDPIN, HIGH);
 
   // Serial Console
   Serial.begin(115200);

	// Initi 3Button
	pinMode(__PINA, INPUT);
	digitalWrite(__PINA, HIGH);
	pinMode(__PINB, INPUT);
	digitalWrite(__PINB, HIGH);
	pinMode(__PINC, INPUT);
	digitalWrite(__PINC, HIGH);
 
}
 
void loop()
{
  // read 3button
  int button = (digitalRead(__PINA) | digitalRead(__PINB)<<1 | digitalRead(__PINC)<<2) ^ 7;
  byte Type=0, Crc;
  unsigned int Device=0x0707, Data=0;
  if (button == 1) {
	digitalWrite(LEDPIN,HIGH);
	Data=0x98; //power off
	Crc=~Data;
    Samsung::SendCommand(Type, Device, Data, Crc);
	delay(500);
  } else if (button == 2) {
	Data=0x3B; //FACTORY
	Crc=~Data;
    Samsung::SendCommand(Type, Device, Data, Crc);
	delay(300);
	Data=0x3C; //3SPEED
	Crc=~Data;
    Samsung::SendCommand(Type, Device, Data, Crc);
	delay(300);
	digitalWrite(LEDPIN,HIGH);
  } else if (button == 4) {
	Data=0x1F; //INFO
	Crc=~Data;
    Samsung::SendCommand(Type, Device, Data, Crc);
	delay(300);
	Data=0x01; //MENU
	Crc=~Data;
    Samsung::SendCommand(Type, Device, Data, Crc);
	delay(300);
	Data=0x0F; //MUTE
	Crc=~Data;
    Samsung::SendCommand(Type, Device, Data, Crc);
	delay(300);
	Data=0x99; //PowerON
	Crc=~Data;
    Samsung::SendCommand(Type, Device, Data, Crc);
	delay(300);
	digitalWrite(LEDPIN,HIGH);
  } else {
	digitalWrite(LEDPIN,LOW);
  }
}

