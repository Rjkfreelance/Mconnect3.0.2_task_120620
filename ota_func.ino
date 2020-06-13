void progress(DlState state, int percent){ //Show % Progress Download Firmware from Server
  Serial.printf("state = %d - percent = %d %c\n", state, percent,'%');//Print format show % progress
     prog = percent; 
     ota_t = millis() - startota;
     chk_ota_timeout(ota_t);//Call function for check timeout
 }
 
/*  Refer to errorCallback method in HttpFOTA.h   */
void error(char *message){ //Show Error Message During OTA
  printf("%s\n", message);
}

/*  Refer to startDownloadCallback method in HttpFOTA.h  */
void startDl(void){ // Start Download Firmware Function
  startota = millis();
}

void endDl(void){ //Show Time to OTA Finish Function 
  ota_t = millis() - startota;
  float otafinish = ota_t/1000.0;  //Sec
  Serial.print(String(ota_t) + " ms ");
  Serial.print(otafinish,2);
  Serial.println(" Sec.");
}

void chk_ota_timeout(unsigned long tm){ //Check TimeOut OTA Function 
  if((tm >= otatimeout)&&(prog < 100)){
   Serial.printf(" Time out! %d\n",tm);
   delay(50);
   ESP.restart();
  }
}

void function_ota()
{
  /*-------------------FOR OTA--------------------------*/
  switch (state)
  {
    case Runnning_e:

      if (!client.connected()) {
        mqttconnect();
      }

      client.loop();
      break;
    case Fota_e:
      DlInfo info;
      info.url = url;
      // info.caCert = NULL;//if only use http then remember to set this to NULL
      info.caCert =  certssl; //SSL Cert iotfmx.com (secure server load from certi.txt)
      info.md5 = md5_1; // info.md5 is argument of setMD5(const char * expected_md5) in Update.h
      info.startDownloadCallback =  startDl;
      info.endDownloadCallback =    endDl;
      info.progressCallback  = progress;
      info.errorCallback     = error;
      int result = httpFOTA.start(info); //OTA Method
      if(result < 0){ // Check error return from class HttpFOTA
        delay(100);
        ESP.restart(); 
      }
      if(result == 1){
       String DT =  DateTimeNOW();
               DT += " OTA OK";
        client.publish(ackota,DT.c_str(),Qos);
        delay(1000);
        ESP.restart();  
      }
     break;
  }
}
