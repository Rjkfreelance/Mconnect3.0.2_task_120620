void packdata_HEADSDCARD() {

  Headerhistory = "";
  DATA_PACKHEADHIS[0] = 0x23;
  DATA_PACKHEADHIS[1] = 0x52; //#Serial
  DATA_PACKHEADHIS[2] = 0x3B;
  DATA_PACKHEADHIS[3] = DATA_PACKHEAD[3];
  DATA_PACKHEADHIS[4] = DATA_PACKHEAD[4];
  DATA_PACKHEADHIS[5] = DATA_PACKHEAD[5];
  DATA_PACKHEADHIS[6] = DATA_PACKHEAD[6];
  DATA_PACKHEADHIS[7] = DATA_PACKHEAD[7];
  DATA_PACKHEADHIS[8] = DATA_PACKHEAD[8];
  DATA_PACKHEADHIS[9] = DATA_PACKHEAD[9];
  DATA_PACKHEADHIS[10] = DATA_PACKHEAD[10];
  DATA_PACKHEADHIS[11] = DATA_PACKHEAD[11];
  DATA_PACKHEADHIS[12] = DATA_PACKHEAD[12];
  DATA_PACKHEADHIS[13] = DATA_PACKHEAD[13];
  DATA_PACKHEADHIS[14] = DATA_PACKHEAD[14];
  DATA_PACKHEADHIS[15] = 0x3B;
  for (int i = 0; i < sizeof(DATA_PACKHEADHIS); i++) {
    Headerhistory += DATA_PACKHEADHIS[i];
    delay(10);
  }
  Serial.print("packdata_HEADSDCARD : ");
  Serial.println(Headerhistory);
}

void packdata_HEAD()
{

  DATA_PACKHEAD[0] = 0x23;
  DATA_PACKHEAD[1] = 0x4D; //#Serial
  DATA_PACKHEAD[2] = 0x3B;
  DATA_PACKHEAD[3] = Chipid_buf[0];
  DATA_PACKHEAD[4] = Chipid_buf[1];
  DATA_PACKHEAD[5] = Chipid_buf[2];
  DATA_PACKHEAD[6] = Chipid_buf[3];
  DATA_PACKHEAD[7] = Chipid_buf[4];
  DATA_PACKHEAD[8] = Chipid_buf[5];
  DATA_PACKHEAD[9] = Chipid_buf[6];
  DATA_PACKHEAD[10] = Chipid_buf[7];
  DATA_PACKHEAD[11] = Chipid_buf[8];
  DATA_PACKHEAD[12] = Chipid_buf[9];
  DATA_PACKHEAD[13] = Chipid_buf[10];
  DATA_PACKHEAD[14] = Chipid_buf[11];
  DATA_PACKHEAD[15] = 0x3B;
  DATA_PACKHEAD[16] = v_fw[0];
  DATA_PACKHEAD[17] = v_fw[1];
  DATA_PACKHEAD[18] = v_fw[2];
  DATA_PACKHEAD[19] = v_fw[3];
  DATA_PACKHEAD[20] = 0x3B;
  if (buf_head == 0) {
    for (int i = 0; i < sizeof(DATA_PACKHEAD); i++)
    {
      mac.packet_header += DATA_PACKHEAD[i];
    }
    buf_head = 1;
    delay(10);
  }


}

void packdata_DATE()
{
  sDate = "";
  DateTime now = RTC.now();
  DATA_PACKDATE[0] = now.day();
  DATA_PACKDATE[1] = now.month();
  DATA_PACKDATE[2] = now.year() - 2000;
  DATA_PACKDATE[3] = now.hour();
  DATA_PACKDATE[4] = now.minute();
  DATA_PACKDATE[5] = now.second();
  
  //sprintf(buf_date, "%02u%02u%02u%02u%02u%02u",now.day(),now.month(),now.year()-2000,now.hour(),now.minute(),now.second());
  
  sprintf(buf_date, "%02u%02u%02u%02u%02u%02u", now.year() - 2000, now.month(), now.day(), now.hour(), now.minute(), now.second());
  for (int i = 0; i < sizeof(buf_date); i++)
  {
    sDate += buf_date[i];
  }
  filenames = sDate;
  sDate += ";";
  delay(50);
}

void packdata_IO()
{
  data_IO = (IO_8 << 7) | (IO_7 << 6) | (IO_6 << 5) | (IO_5 << 4) | (IO_4 << 3) | (IO_3 << 2) | (IO_2 << 1) | (IO_1 << 0);
  DATA_PACKIO[0] = 00;
  DATA_PACKIO[1] = data_IO;
  sprintf(buf_io, "%02X%02X", DATA_PACKIO[0], DATA_PACKIO[1]);
}

void packdata_PWM()
{
  DATA_PACKPWM1[0] = 11;
  DATA_PACKPWM1[1] = 11;
  DATA_PACKPWM1[2] = 11;
  DATA_PACKPWM1[3] = 11;

  DATA_PACKPWM2[0] = 11;
  DATA_PACKPWM2[1] = 11;
  DATA_PACKPWM2[2] = 11;
  DATA_PACKPWM2[3] = 11;
}

void packdata_RELAY()
{
  DATA_PACKRELAY[0] = 11;
}

void packdata_PWM2()
{
  DATA_PACKPWM3[0] = 11;
  DATA_PACKPWM3[1] = 11;
  DATA_PACKPWM3[2] = 11;
  DATA_PACKPWM3[3] = 11;

  DATA_PACKPWM4[0] = 11;
  DATA_PACKPWM4[1] = 11;
  DATA_PACKPWM4[2] = 11;
  DATA_PACKPWM4[3] = 11;
}

void packdata_AD()
{
  DATA_PACKAD1[0] = 11;
  DATA_PACKAD1[1] = 11;
  DATA_PACKAD1[2] = 11;
  DATA_PACKAD1[3] = 11;

  DATA_PACKAD2[0] = 11;
  DATA_PACKAD2[1] = 11;
  DATA_PACKAD2[2] = 11;
  DATA_PACKAD2[3] = 11;

  DATA_PACKAD3[0] = 11;
  DATA_PACKAD3[1] = 11;
  DATA_PACKAD3[2] = 11;
  DATA_PACKAD3[3] = 11;
}

void packdata_GPS()
{
  DATA_PACKGPS[0] = 11;
  DATA_PACKGPS[1] = 11;
  DATA_PACKGPS[2] = 11;
  DATA_PACKGPS[3] = 11;
  DATA_PACKGPS[4] = 11;
  DATA_PACKGPS[5] = 11;
  DATA_PACKGPS[6] = 11;
}



void packdata_M1()
{
  DATA_PACKM1[0] = 11;
  DATA_PACKM1[1] = 11;
  DATA_PACKM1[2] = 11;
  DATA_PACKM1[3] = 11;
  DATA_PACKM1[4] = 11;
  DATA_PACKM1[5] = 11;
  DATA_PACKM1[6] = 11;
  DATA_PACKM1[7] = 11;
}

void packdata_M2()
{
  DATA_PACKM2[0] = 11;
  DATA_PACKM2[1] = 11;
  DATA_PACKM2[2] = 11;
}

void packdata_M3()
{
  DATA_PACKM3[0] = 11;
  DATA_PACKM3[1] = 11;
  DATA_PACKM3[2] = 11;
}

void adcbegin()
{
  if (!adc.begin(18, 23, 19, 15))
  {
    Serial.print("Initializing MCP3008...Failed");
  }
  Serial.println("initialization MCP3008 done.");
  delay(100);
}
