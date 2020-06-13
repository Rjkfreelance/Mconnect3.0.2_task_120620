void sendconfig(){ 
         chipid=ESP.getEfuseMac();
         (uint16_t)(chipid>>32);
         String cID = String((uint16_t)(chipid>>32),HEX);//Revise By RJK
         String eID = String((uint32_t)chipid,HEX);//Revise By RJK
         cID.toUpperCase();
         eID.toUpperCase();
         String id = "id|" +cID + eID; id += "$"; //pack chip id
         String v = String(v_fw[0])+String(v_fw[1])+String(v_fw[2])+String(v_fw[3]); v = "v|" + v + "$";//pack version firmware
         String w = String(wifi_ssid); w = "w|"+w+"$";// pack WiFi SSID
         String wp = String(wifi_pwd); wp = "p|"+ wp + "$";// pack WiFi Password
         String ms = String(mqtt_server); ms = "ms|"+ ms + "$";// pack mqtt server
         String mp = String(mqttPort,DEC); mp = "mp|" + mp + "$"; //pack mqtt port 
         String u = String(mqttUser); u = "u|" + u + "$";//pack mqtt user 
         String mw = String(mqttPassword); mw = "mw|" + mw +"$"+String(getconf);//pack mqtt password
         String cfg = id + v + w + wp + ms + mp + u + mw; //Concatination 
         client.publish(sendconf,("CF$" +cfg).c_str()); //Publish to Cloud
}

void sendId(){
         chipid=ESP.getEfuseMac();
         (uint16_t)(chipid>>32);
         String cID = String((uint16_t)(chipid>>32),HEX);//Revise By RJK
         String eID = String((uint32_t)chipid,HEX);//Revise By RJK
         cID.toUpperCase();
         eID.toUpperCase();
         client.publish(sendconf,(cID+eID).c_str()); //Publish to Cloud
}
/*
     Machine Publish Configs to cloud if subscribe CONFIG_TOPIC Callback function call this function
     For mat data packet with delimeter $ between each value and | each key|value
     such as CF$id|chipid$v|version$w|WiFi SSID$p|WiFi Password$ms|mqttserver$mp|mqtt port$u|mqtt user$mw|mqtt password$config topic 
     CF is config header , id is chip id , v is version , w is WiFi SSID , p is WiFi password , ms is mqttserver ,mp is mqtt port , u is mqtt user
        mw is mqtt password , CFG Topic 
     such as get config  of machine G00001/C01/M001 
     CF$id|c49b38e0d84$v|AB01V1$w|FMX-Wireless$p|fmxfmxfmx$ms|m20.cloudmqtt.com$mp|11580$u|jqgehwzu$mw|Xmrb3tebPNY6$CFG/G00001/C01/M001         
*/

String CheckCertSSL(){
   String url = "https://www.iotfmx.com/iot/api/iotapi_checkcert.php?cid="+ String(clientId);
   Serial.println("Check use Certificate SSL from Server: " + url);
   HTTPClient http;
   http.begin(url, certssl);
   int httpCode = http.GET();
   if (httpCode == 200){
    String reply = http.getString();
    return reply;
   } else {
   Serial.println("Fail. error code " + String(httpCode));
   return "Fail";
  }
}
void ChangeConfig_Restart(){
  String url = "https://www.iotfmx.com/iot/api/iotapi_getconfig.php?getcfg="+ String(clientId);
 Serial.println();
 Serial.println("Get Coonfig from Server: " + url);
 HTTPClient http;
 http.begin(url, certssl);
  int httpCode = http.GET();
 if (httpCode == 200){
   String content = http.getString();
   Serial.println(content);
    WriteSDcfg(SD,"/conf.txt",content);
    client.publish(sendconf,"Write Config OK",Qos);
    digitalWrite(RST,!digitalRead(RST));
    delay(500);
    
   
  } else {
   Serial.println("Fail. error code " + String(httpCode));
  }
}


void ChangeConfig(){
 String url = "https://www.iotfmx.com/iot/api/iotapi_getconfig.php?getcfg="+ String(clientId);
 Serial.println();
 Serial.println("Get Coonfig from Server: " + url);
 HTTPClient http;
 http.begin(url, certssl);
  int httpCode = http.GET();
 if (httpCode == 200){
   String content = http.getString();
   Serial.println(content);
    WriteSDcfg(SD,"/conf.txt",content);
    client.publish(sendconf,"Write Config OK",Qos);
  } else {
   Serial.println("Fail. error code " + String(httpCode));
  }
}

void currentConfig(fs::FS &fs, const char* path){

  String Content="";
  File frc = fs.open(path);
  if (!frc) {
    Serial.println("Failed to open directory");
    return;
  }
  while(frc.available()){
     Content += frc.readStringUntil('\n');
    }
   frc.close();
  Serial.println(Content);
  client.publish(sendconf,Content.c_str());
}
