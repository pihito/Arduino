#include <SPI.h>
#include <Ethernet.h>
#include <LiquidCrystal_I2C.h>


#include <Wire.h> 


//Request to command an X10 appliance
//IP/X10/<appliance addr>/?p1=<1(on)|0(off)>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

String readString = String(""); //string for fetching data from address

// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // start the Ethernet connection and the server:
  Ethernet.begin(mac);
  server.begin();
  //print IP on serial
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  //initialise LCD and print IP adress
  lcd.begin(16,2);         // initialize the lcd for 16 chars 2 lines and turn on backlight
  lcd.setCursor(0,0); 
  lcd.print(Ethernet.localIP());
}

void writeJsonOkHeader(EthernetClient client)
{
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/json");
  client.println("Connection: close");  // the connection will be closed after completion of the response
  //client.println("Refresh: 5");  // refresh the page automatically every 5 sec
  client.println();
}


void writeLCDL2(String text)
{
  lcd.setCursor(0,0); 
  lcd.print(Ethernet.localIP());
  lcd.setCursor(0,1); 
  lcd.print(text);

}

//retrun X10 JSON to web client: 
//{"X10": {"status": true,"adress": "C01"}
void performX10Request(EthernetClient client,char cHouseCode,int iUnitCode,boolean bSatut)
{
  // send a standard http response header
  writeJsonOkHeader(client);
  client.print("{\"X10\": {\"status\": ");
  client.print(bSatut);
  client.print(",\"address\": \"");
  client.print(cHouseCode);
  client.print(iUnitCode);
  client.print("\"}}"); 
  String text ="X10 : " ;
  text += cHouseCode;
  text += iUnitCode;
  text += ':';
  text += bSatut;
  writeLCDL2(text);

}


void sendError(EthernetClient client,String reason)
{
  // send a standard http response header
  client.println("HTTP/1.1 400 BAD REQUEST");
  client.print("Reason-Phrase:");
  client.println(reason);
  client.println("Content-Type: text/html");
  client.println("Connection: close");  // the connection will be closed after completion of the response
  //client.println("Refresh: 5");  // refresh the page automatically every 5 sec
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println(reason);
  client.println();
  client.println("</html>");
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100) {
          //store characters to string 
          readString.concat(c); 
        } 
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {

          ///**********************Request type X10*************************///
          int iEndOfRoot = readString.indexOf("X10/");
          int iEndOfParam = readString.indexOf("?p1=");
          //read the request : X10 - X10/<appliance addr>?p1=<on|off>
          if( ( iEndOfRoot != -1) && (iEndOfParam != -1) ) {
            Serial.println("recieve X10 request");
            char cApplianceLetter = 'A';
            String sApplianceNbr = String(3);
            String cApplianceValue = String(3);

            cApplianceLetter = readString[iEndOfRoot+4];
            sApplianceNbr = readString.substring(iEndOfRoot+5,iEndOfRoot+7);
            cApplianceValue = readString.substring(iEndOfParam+4,iEndOfParam+6); 
            Serial.println(cApplianceLetter);
            Serial.println(sApplianceNbr);
            Serial.println(cApplianceValue);
            int iApplianceNbr = sApplianceNbr.toInt();
            int iApplianceValue = cApplianceValue.toInt();
            if(cApplianceLetter >='A' && cApplianceLetter <= 'P' && iApplianceNbr > 0 && iApplianceNbr < 17 && (iApplianceValue ==0 || iApplianceValue ==1 ))
              performX10Request(client,cApplianceLetter,iApplianceNbr,iApplianceValue);
            else
              sendError(client,"Request must have correct X10 value");
          }  
          else
          {
            sendError(client,"Request must be : IP/X10/<appliance addr>/?p1=<1(on)|0(off)>");
          }
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
    readString = String(100);
  }
}


