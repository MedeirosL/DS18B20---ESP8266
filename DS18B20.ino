#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS D1 // Data wire is plugged into pin D1
#define precision 12 // OneWire precision Dallas Sensor

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress T1, T2, T3, T4, T5; // arrays to hold N devices addresses
void setup(void){
  Serial.begin(115200); //Start serial port
  DS18B20Setup();
}
void DS18B20Setup(){ //setup devices
  Serial.println("\n\nDS18B20 Devices: ");
  sensors.begin();
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");
  if (!sensors.getAddress(T1, 0)) 
    Serial.println("Sensor 1 not found.");
  if (!sensors.getAddress(T2, 1)) 
    Serial.println("Sensor 2 not found.");
  if (!sensors.getAddress(T3, 2)) 
    Serial.println("Sensor 3 not found.");
  if (!sensors.getAddress(T4, 3)) 
    Serial.println("Sensor 4 not found.");
  if (!sensors.getAddress(T5, 4)) 
    Serial.println("Sensor 5 not found.");
  Serial.println();
  for (int k =0; k < sensors.getDeviceCount(); k++) {
    Serial.print("Sensor "); Serial.print(k+1);
    Serial.print(" Address: ");
    if (k == 0) { 
      printAddress(T1); Serial.println();
    } 
    else if (k == 1) { 
      printAddress(T2); Serial.println();
    } 
    else if (k == 2) { 
      printAddress(T3); Serial.println();
    } 
    else if (k == 3) { 
      printAddress(T4); Serial.println();
    } 
    else if (k == 4) { 
      printAddress(T5); Serial.println();
    } 
    Serial.println();
    
  }
  sensors.setResolution(T1, precision); //set resolution func
  sensors.setResolution(T2, precision);
  sensors.setResolution(T3, precision);
  sensors.setResolution(T4, precision);
  sensors.setResolution(T5, precision);
  Serial.println();

  for (int k =0; k < sensors.getDeviceCount(); k++) {
    Serial.print("Sensor "); 
    Serial.print(k+1);
    Serial.print(" Prcision: ");
    if (k == 0) { 
      Serial.print(sensors.getResolution(T1), DEC); 
      Serial.println();
    } 
    else if (k == 1) { 
      Serial.print(sensors.getResolution(T2), DEC); 
      Serial.println();
    } 
    else if (k == 2) { 
      Serial.print(sensors.getResolution(T3), DEC); 
      Serial.println();
    } 
    else if (k == 3) { 
      Serial.print(sensors.getResolution(T4), DEC); 
      Serial.println();
    } 
    else if (k == 4) { 
      Serial.print(sensors.getResolution(T5), DEC); 
      Serial.println();
    } 
    
  }
}
  
  void printAddress(DeviceAddress deviceAddress){ //print Address func
    for (uint8_t i = 0; i < 8; i++){
      if (deviceAddress[i] < 16) 
        Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
    }
  }


float readSensor(DeviceAddress deviceAddress){ //read func
  Serial.print("Endereço: ");
  for (uint8_t i = 0; i < 8; i++){
    if (deviceAddress[i] < 16) 
      Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print(" Temp.: ");
 
  return(tempC);
  
}


void loop(void){
  float t1,t2,t3,t4,t5;
  Serial.print("Reading Sensors..."); sensors.requestTemperatures(); Serial.println(" Ok!");
  for (int k =0; k < sensors.getDeviceCount(); k++) {
    Serial.print("Sensor "); Serial.print(k+1); Serial.print(" ");
    if (k == 0)
      {t1=readSensor(T1); Serial.println(t1);}
    else if (k == 1)
      {t2=readSensor(T2); Serial.println(t2);}
    else if (k == 2)
      readSensor(T3); //printData(T3);
    else if (k == 3)
      readSensor(T4); //printData(T4);
    else if (k == 4)
      readSensor(T5); //printData(T5);
  }
  Serial.println();
  delay(2000);
}
