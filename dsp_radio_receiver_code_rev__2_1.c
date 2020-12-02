/*******************************************************************************************************************************************************
  SI4735/30 AM/FM STEREO - LW/MW/SW/CB RADIO RECEIVER WITH ST7735 COLOR TFT (LIB TFT_ST7735 BODMER) ARDUINO NANO/UNO/PRO MINI - WRITE BY JCR FEB/2020
  RECEPTION RANGE: AM 150kHz TO 30MHz - FM 64 TO 108MHz
  VERSION TO SHARE - JUN/2020
  REV.2.1 - NOV/2020
********************************************************************************************************************************************************
  ELECTRIC CONNECTIONS (ALSO SEE THE SCHEMATICS):
  ST7735 DISPLAY PIN CONNECTION TO ARDUINO NANO/UNO/PRO MINI:
  LED (BACKLIGHT) - 5V(VIA 100R RESISTOR SERIES); SCK - D13; SDA - D11; AO - D9; RESET - D8; CS - D10; GND - GND; VCC - 5V
  ROTARY ENCODER TO ARDUINO: D2; GND; D3
  PUSH BUTTONS:
  BAND SELECT - A0; TUNING STEPS (1k / 5k / 10k) - A1; AM IF FILTER SEL - A2; COLOR THEME - A3 (NOTE: THE OTHER SIDE OF P.B. IS CONNECTED TO GND)
  SI4735/30: SDA - A4 (VIA 1k RESISTOR SERIES); SCL - A5 (VIA 1k RESISTOR SERIES); RESET - D7 (VIA 10k RESISTOR SERIES); VCC - 3.3V; GND - GND
*********************************************************************************************************************************************************
  ATTENTION!
  -MUST INSTALL AND USE THE LIBRARIES LOCATED IN "INSTALL THESE LIBRARIES" FOLDER
  -PLEASE BELOW CHOOSE THE CORRECT I2C ADDRESS FOR YOUR SI4730/35 (0x11 OR 0x63), BEFORE TO START. MODULE PL102BA-S V2.11 USE 0x63
  -FOLLOW THE WIRING AS INDICATED ON SCHEMATICS
  -WORKS WITH IC SI4730-D60 AND SI4731/32/34/35 OR RADIO MODULE PL102BA-S V2.11
  -FOR ICs SI4730/31/34/35 - D60  A 10k PULLUP RESISTOR MUST BE USED IN EACH I2C LINES. FOR PL102BA-S MODULE PULLUPS NOT REQUIRED
*********************************************************************************************************************************************************/

#include <SPI.h>
#include "Wire.h"
#include <TFT_ST7735.h> //BODMER graphics and font library for ST7735 driver chip
#include <Si4735.h>     //MICHAEL KENNEDY SI4735 I2C library modified by JCR
#include <Rotary.h>     //BUXTON Rotary encoder library

TFT_ST7735 tft = TFT_ST7735();  //Invoke library, pins defined in User_Setup.h
Rotary r = Rotary(2, 3);
Si4735 radio;

const byte band = A0;     //Band select and Switch encoder Tune
const byte frstep = A1;   //Tuning Step
const byte filtsel = A2;  //IF filter select
const byte modesel = A3;  //Change diaplay color theme

byte SI7435_ADDRESS = 0x63; //I2C ADDRESS OF SI4735: 0x11 (SEN PIN TO GND) or 0x63 (SEN PIN TO 3v3)

const int bl[22] = {"160 ", "120 ", "90m ", "80m ", "75m ", "60m ", "49m ", "40m ", "41m ", "31m ", "30m ",
                    "25m ", "22m ", "20m ", "19m ", "17m ", "16m ", "15m ", "13m ", "12m ", "11m ", "10m "
                   };
unsigned int freq;
unsigned int fstep;
unsigned int freqold;
int sm, sm_old, mx, mod;
int stp = 2;
int mode = 2;
byte encoder = 1;
byte count = 6;
byte filter = 0x03;
byte fil = 4;
byte fr_h;
byte fr_l;
byte ssb_m = 0x00; //0x00 AM;
byte mw_sw = 0x00; //0x00 MW ; 0x01 SW
byte am_fm = 0x40; //0x40 AM ; 0x20 FM
int period = 100;  //millis period timer for refresh RSQ
unsigned long time_now = 0;  //millis init timer for refresh RSQ
int period_sm = 1000;  //millis period timer for S-meter val peak hold
unsigned long time_now_sm = 0;  //millis init timer S-meter val peak hold

uint16_t ca = 0x001F;  //Blue - tela de fundo
uint16_t cb = 0xFFFF;  //White - textos unidades (ORIG 0x07FF Cyan)
uint16_t cc = 0xFFFF;  //White - linhas
uint16_t cd = 0x3FE0;  //Green - barra SM
uint16_t ce = 0xF81F;  //Magenta - barra MD
uint16_t cf = 0x0000;  //Black - barra inv SM/MD
uint16_t cg = 0xFFFF;  //White - display e kHz
uint16_t ch = 0x07FF;  //Cyan - barra RIT

void setup() {
  tft.init();
  tft.setRotation(3);
  SPI.begin();
  Wire.begin();
  start_msg();
  tft.fillScreen(ca);

  pinMode(band, INPUT_PULLUP);
  pinMode(frstep, INPUT_PULLUP);
  pinMode(filtsel, INPUT_PULLUP);
  pinMode(modesel, INPUT_PULLUP);

  radio.begin(0, SI7435_ADDRESS);
  power_up_norm();
  delay(400);
  am_command();
  count = 6;      //Define initial band at startup
  bandpresets();
  layout();
  setstep();
  frequency();
  smeter();
  band_ind();
  filterAM();

  PCICR |= (1 << PCIE2);
  PCMSK2 |= (1 << PCINT18) | (1 << PCINT19);
  sei();
}

void loop() {
  if (freqold != freq) {
    freqold = freq;
    tune_freq();
    frequency();
  }

  if ((digitalRead(band)) == LOW) {
    inc_preset();
    while (digitalRead(band) == LOW);
  }

  if ((digitalRead(frstep)) == LOW) {
    if (am_fm != 0x20) inc_step();
    if (am_fm == 0x20) setstepFM();
    while (digitalRead(frstep) == LOW);
  }

  if ((digitalRead(filtsel)) == LOW) {
    if (am_fm != 0x20) filterAM();
    if (am_fm == 0x20) filterFM();
    while (digitalRead(filtsel) == LOW);
  }

  if (digitalRead(modesel) == LOW) {
    delay(500);
    ca = 0x0000;  //Black
    cb = 0xFFFF;  //White
    cc = 0xFFFF;  //White
    cd = 0xF81F;  //Magenta   //0x001F;  //Blue
    ce = 0xF81F;  //Magenta
    cg = 0x3FE0;  //Green
    ch = 0x07FF;  //Cyan
    tft.fillScreen(ca);
    tft.setTextColor(cb, ca);
    layout();
    bandpresets();
    frequency(); 
    if (am_fm != 0x20) {fil = 4; filterAM();}
    if (am_fm == 0x20) {fil = 0; filterFM();}
  }

  if (millis() > time_now + period) {
    time_now = millis();
    rsq();
    smeter();
    modgraf();
    if (am_fm != 0x20) band_ind();
    if (am_fm == 0x20) pilot();
  }

  if (sm > mx) mx = sm;
  if (millis() - time_now_sm >= period_sm) {
    time_now_sm = millis();
    mx = sm;
  }
}

ISR(PCINT2_vect) {
  char result = r.process();
  if (result == DIR_CW)
    set_frequency(1);
  else if (result == DIR_CCW)
    set_frequency(-1);
}

void set_frequency(short dir) {
  if (encoder == 1) {     //AM band limits
    if (dir == 1) freq = freq + fstep;
    if (freq >= 30000) freq = 30000;
    if (dir == -1) freq = freq - fstep;
    if (freq <= 150) freq = 150;
  }
  if (encoder == 2) {     //FM band limits
    if (dir == 1) freq = freq + fstep;
    if (freq >= 10810) freq = 10810;
    if (dir == -1) freq = freq - fstep;
    if (freq <= 6410) freq = 6410;
  }
}

void inc_preset() {
  count++;
  if (count > 15)
    count = 1;
  bandpresets();
  delay(50);
}

void bandpresets() {
  tft.setTextSize(1);
  tft.setTextColor(cb, ca);
  switch (count)  {
    case 1:
      encoder = 1;
      radio.begin(0, SI7435_ADDRESS);
      power_down();
      power_up_norm();
      delay(200);
      ssb_m = 0x00;
      freq = 198;
      am_fm = 0x40;
      tune_freq();
      am_command();
      filter = 0x03;
      stp = 1;
      setstep();
      tft.drawString("LW1       ", 30, 57, 2);
      tft.drawString("2k ", 135, 74, 2);
      break;
    case 2:
      freq = 620;
      stp = 3;
      setstep();
      tft.drawString("MW1", 30, 57, 2);
      break;
    case 3:
      freq = 1130;
      stp = 3;
      setstep();
      tft.drawString("MW2", 30, 57, 2);
      break;
    case 4:
      freq = 3700;
      stp = 1;
      setstep();
      break;
    case 5:
      freq = 5000;
      stp = 2;
      setstep();
      break;
    case 6:
      freq = 6180;
      stp = 2;
      setstep();
      break;
    case 7:
      freq = 7205;
      stp = 1;
      setstep();
      break;
    case 8:
      freq = 10000;
      stp = 2;
      setstep();
      break;
    case 9:
      freq = 11940;
      stp = 2;
      setstep();
      break;
    case 10:
      freq = 13790;
      stp = 2;
      setstep();
      break;
    case 11:
      freq = 15400;
      stp = 2;
      setstep();
      break;
    case 12:
      freq = 17780;
      stp = 2;
      setstep();
      break;
    case 13:
      freq = 21525;
      stp = 2;
      setstep();
      break;
    case 14:
      freq = 27015;
      stp = 1;
      setstep();
      break;
    case 15:
      encoder = 2;
      power_down();
      power_up_FM();
      delay(200);
      am_fm = 0x20;
      ssb_m = 0x00;
      freq = 10050;
      fstep = 10;
      tune();
      radio.setMode(FM);
      fil = 0; filterFM();
      stp = 0; setstepFM();
      break;
  }
  if (am_fm == 0x20) {
    tft.setTextColor(cg, ca); tft.drawString("MHz", 132, 57, 2); tft.setTextColor(cb, ca); tft.drawString("FM ", 3, 57, 2);
  }
  else {
    tft.setTextColor(cg, ca); tft.drawString("kHz ", 132, 57, 2); tft.setTextColor(cb, ca); tft.drawString("AM ", 3, 57, 2);
  }
}

void filterAM() {
  tft.setTextSize(1);
  tft.setTextColor(cb, ca);
  switch (fil) {
    case 0:
      fil = 1;
      filter = 0x00; tft.drawString("6k ", 135, 74, 2);
      break;
    case 1:
      fil = 2;
      filter = 0x01; tft.drawString("4k ", 135, 74, 2);
      break;
    case 2:
      fil = 3;
      filter = 0x02; tft.drawString("3k ", 135, 74, 2);
      break;
    case 3:
      fil = 4;
      filter = 0x06; tft.drawString("2k5", 135, 74, 2);
      break;
    case 4:
      fil = 5;
      filter = 0x03; tft.drawString("2k ", 135, 74, 2);
      break;
    case 5:
      fil = 6;
      filter = 0x05; tft.drawString("1k8", 135, 74, 2);
      break;
    case 6:
      fil = 0;
      filter = 0x04; tft.drawString("1k ", 135, 74, 2);
      break;
  }
  property_filter_AM();
}

void filterFM() {
  tft.setTextSize(1);
  tft.setTextColor(cb, ca);
  switch (fil) {
    case 0:
      fil = 1;
      filter = 0x00; tft.drawString("Aut", 135, 74, 2);
      break;
    case 1:
      fil = 2;
      filter = 0x01; tft.drawString("110", 135, 74, 2);
      break;
    case 2:
      fil = 3;
      filter = 0x02; tft.drawString("84k", 135, 74, 2);
      break;
    case 3:
      fil = 4;
      filter = 0x03; tft.drawString("60k", 135, 74, 2);
      break;
    case 4:
      fil = 0;
      filter = 0x04; tft.drawString("40k", 135, 74, 2);
      break;
  }
  fm_command();
}

void inc_step() {
  stp++;
  if (stp > 3)
    stp = 1;
  setstep();
  delay(50);
}

void setstep() {
  tft.setTextSize(1);
  tft.setTextColor(cb, ca);
  switch (stp) {
    case 1:
      fstep = 1;    // 1kHz
      tft.drawString("1k ", 100, 57, 2);
      break;
    case 2:
      fstep = 5;    // 5kHz
      tft.drawString("5k ", 100, 57, 2);
      break;
    case 3:
      fstep = 10;  // 10kHz
      tft.drawString("10k", 100, 57, 2);
      break;
  }
}

void setstepFM() {
  tft.setTextSize(1);
  tft.setTextColor(cb, ca);
  switch (stp) {
    case 0:
      stp = 1;
      fstep = 10;    // 100kHz
      tft.drawString(" x1", 100, 57, 2);
      break;
    case 1:
      stp = 0;
      fstep = 20;    // 200kHz
      tft.drawString(" x2", 100, 57, 2);
      break;
  }
}

void frequency() {    //Format of frequency numbers
  tft.setTextColor(cg, ca);
  if (freq >= 10000) tft.drawNumber(freq, 0, 1, 7); if (freq < 10000 && freq >= 1000) tft.drawNumber(freq, 32, 1, 7);
  if (freq < 1000 && freq >= 100) tft.drawNumber(freq, 64, 1, 7); if (freq < 100 && freq >= 10) tft.drawNumber(freq, 96, 1, 7);
  if (freq < 10) tft.drawNumber(freq, 128, 1, 7); if (freq < 10000) tft.fillRect (2, 1, 28, 48, ca);
  if (freq < 1000) tft.fillRect (34, 1, 28, 48, ca);

  if (am_fm == 0x40 && freq >= 1000) tft.fillCircle(63, 51, 2, cg); else  tft.fillCircle(63, 51, 2, ca);
  if (am_fm == 0x20) tft.fillCircle(95, 51, 2, cg);  else tft.fillCircle(95, 51, 2, ca);
}

void smeter() {  //BARGRAPH SIGNAL METER
  if (sm > 90) sm = 90;

  tft.fillRect(31, 111, sm, 14, cd); // BAR DIRECT
  tft.fillRect(31 + sm, 111, 90 - sm, 14, ST7735_BLACK); // BAR INVERSE

  tft.setTextSize(1);
  tft.setTextColor(cb, ca);
  if (mx < 1) tft.drawString("S0 ", 136, 110, 2);
  if ((mx >= 1) && (mx < 10)) tft.drawString("S1 ", 136, 110, 2);
  if ((mx >= 10) && (mx < 25)) tft.drawString("S3 ", 136, 110, 2);
  if ((mx >= 25) && (mx < 35)) tft.drawString("S5 ", 136, 110, 2);
  if ((mx >= 35) && (mx < 55)) tft.drawString("S7 ", 136, 110, 2);
  if ((mx >= 55) && (mx < 65)) tft.drawString("S9 ", 136, 110, 2);
  if ((mx >= 65) && (mx < 75)) tft.drawString("+20", 136, 110, 2);
  if ((mx >= 75) && (mx < 80)) tft.drawString("+40", 136, 110, 2);
  if (mx >= 80) tft.drawString("+60", 136, 110, 2);
}

void modgraf() {  //BARGRAPH SIGNAL TO NOISE
  int mod_g = map(mod, 0, 65, 65, 0);
  tft.fillRect(26, 77, mod_g, 10, ch); // BAR DIRECT
  tft.fillRect(26 + mod_g, 77, 65 - mod_g, 10, ST7735_BLACK); // BAR INVERSE
}

void layout() {
  tft.setTextColor(TFT_WHITE, TFT_BLUE);
  tft.drawFastHLine(0, 56, 160, cc);  //125
  tft.drawFastVLine(125, 56, 20, cc);
  tft.drawFastHLine(0, 73, 160, cc);
  tft.drawFastHLine(0, 90, 160, cc);
  tft.drawFastHLine(0, 107, 160, cc);
  tft.drawFastVLine(125, 107, 20, cc);

  tft.setTextSize(1);
  tft.setTextColor(cb, ca);
  tft.drawString("JCR", 3, 91, 2);
  tft.drawString("DSP All B. Receiver", 30, 91, 2);
  tft.drawString("MD", 3, 74, 2);
  tft.drawString("BWF", 105, 74, 2);
  tft.drawString("S|dB", 3, 110, 2);
}

void start_msg() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("JCR Radio - 2020", 3, 10, 2);
  tft.drawString("DSP ALL BAND RECEIVER", 3, 40, 2);
  tft.drawString("REVISION 2.1", 3, 70, 2);
  delay(2000);
}

void band_ind() {
  tft.setTextSize(1); tft.setTextColor(cb, ca);
  if (freq >= 1800 && freq <= 2000) tft.drawString(bl[0], 30, 57, 2); if (freq >= 2300 && freq <= 2495) tft.drawString(bl[1], 30, 57, 2);
  if (freq >= 3200 && freq <= 3400) tft.drawString(bl[2], 30, 57, 2); if (freq >= 3500 && freq <= 3800) tft.drawString(bl[3], 30, 57, 2);
  if (freq >= 3900 && freq <= 4000) tft.drawString(bl[4], 30, 57, 2); if (freq >= 4750 && freq <= 5500) tft.drawString(bl[5], 30, 57, 2);
  if (freq >= 5700 && freq <= 6200) tft.drawString(bl[6], 30, 57, 2); if (freq >= 7000 && freq <= 7299) tft.drawString(bl[7], 30, 57, 2);
  if (freq >= 7300 && freq <= 7600) tft.drawString(bl[8], 30, 57, 2); if (freq >= 9400 && freq <= 10000) tft.drawString(bl[9], 30, 57, 2);
  if (freq >= 10100 && freq <= 10150) tft.drawString(bl[10], 30, 57, 2); if (freq >= 11600 && freq <= 12100) tft.drawString(bl[11], 30, 57, 2);
  if (freq >= 13570 && freq <= 13870) tft.drawString(bl[12], 30, 57, 2); if (freq >= 14000 && freq <= 14350) tft.drawString(bl[13], 30, 57, 2);
  if (freq >= 15100 && freq <= 15830) tft.drawString(bl[14], 30, 57, 2); if (freq >= 18068 && freq <= 18168) tft.drawString(bl[15], 30, 57, 2);
  if (freq >= 17480 && freq <= 17900) tft.drawString(bl[16], 30, 57, 2); if (freq >= 21000 && freq <= 21450) tft.drawString(bl[17], 30, 57, 2);
  if (freq >= 21451 && freq <= 21850) tft.drawString(bl[18], 30, 57, 2); if (freq >= 24890 && freq <= 24990) tft.drawString(bl[19], 30, 57, 2);
  if (freq >= 25670 && freq <= 27999) tft.drawString(bl[20], 30, 57, 2); if (freq >= 28000 && freq <= 29700) tft.drawString(bl[21], 30, 57, 2);
  if (count == 4 && freq < 1800) tft.drawString("MW2", 30, 57, 2);
}
//----------------------------------------------------------------------------------------------------------------
void tune_freq() {
  fr_h = (freq) >> 8;      //Divide um numero Decimal em dois bytes Hexadecimal, Hi byte e Lo byte
  fr_l = (freq) & 0x00FF;

  if ((freq) < 1800) {     //Switch on/off MW tuning cap - 0x00 - MW ; 0x01 - SW
    mw_sw = 0x00;
  }
  else (mw_sw = 0x01);

  tune();
}

void rsq() {
  RSQMetrics rsq;
  radio.getRSQ(&rsq);
  sm = (rsq.RSSI);
  mod = (rsq.SNR);
}

void pilot() {
  RSQMetrics rsq;
  radio.getRSQ(&rsq);
  tft.setTextSize(1);
  tft.setTextColor(cb, ca);
  if (am_fm == 0x20) {
    if (rsq.stereo == 1)
      tft.drawString("> Stereo <", 30, 57, 2);
    if (rsq.stereo == 0)
      tft.drawString("<  Mono  >", 30, 57, 2);
  }
}

void am_command() {
  radio.setProperty(PROP_AM_SOFT_MUTE_MAX_ATTENUATION, 1); // 0 (OFF) - 63
  radio.setProperty(PROP_AM_AUTOMATIC_VOLUME_CONTROL_MAX_GAIN, 0x32C8); // 0x1000 - 0x7800
  radio.setProperty(PROP_AM_AGC_ATTACK_RATE, 4); // 4–248
  radio.setProperty(PROP_AM_AGC_RELEASE_RATE, 4); // 4–248
}

void fm_command() {
  radio.setProperty(PROP_FM_DEEMPHASIS, 0x0001); // 02 = 75 μs;  01 = 50 μs
  radio.setProperty(PROP_FM_CHANNEL_FILTER, filter); // 0 = automat; 1 = 110kHz; 4 = 40kHz
  radio.setProperty(PROP_FM_SOFT_MUTE_MAX_ATTENUATION, 0); // 0 = disable; 31 = max
  radio.setProperty(PROP_FM_BLEND_STEREO_THRESHOLD, 0); // 0 = stereo; 127 = mono
  radio.setProperty(PROP_FM_BLEND_MONO_THRESHOLD, 0); // 0 = stereo; 127 = mono
}
//----------------------------------------------------------------------------------------------------------------
void power_down() {
  Wire.beginTransmission(SI7435_ADDRESS);
  Wire.write(0x11);
  Wire.endTransmission();
  delay(1);
}

void power_up_norm() {
  Wire.beginTransmission(SI7435_ADDRESS);
  Wire.write(0x01);
  Wire.write(0x11);  //11 - NORM ; 31 - PATCH
  Wire.write(0x05);
  Wire.endTransmission();
  delay(1);
}

void power_up_FM() {
  Wire.beginTransmission(SI7435_ADDRESS);
  Wire.write(0x01);
  Wire.write(0x10);  //10 - NORM ; 30 - PATCH
  Wire.write(0x05);
  Wire.endTransmission();
  delay(1);
}

void tune() {
  Wire.beginTransmission(SI7435_ADDRESS);
  Wire.write(am_fm); //0x40 AM ; 0x20 FM
  Wire.write(ssb_m);
  Wire.write(fr_h);  //Hi byte Tune
  Wire.write(fr_l);  //Lo byte Tune
  Wire.write(0x00);
  Wire.write(mw_sw); //0x00 MW ; 0x01 SW
  Wire.endTransmission();
  delay(1);
}

void property_filter_AM() {
  Wire.beginTransmission(SI7435_ADDRESS);
  Wire.write(0x12);
  Wire.write(0x00);
  Wire.write(0x31);
  Wire.write(0x02);
  Wire.write(0x00);     //0x01 = Low cut filter 100Hz ON - 0x00 = OFF
  Wire.write(filter);   //0x00 = 6kHz; 1 = 4kHz; 2 = 3kHz; 3 = 2kHz; 4 = 1kHz; 5 = 1.8kHz; 6 = 2.5kHz;
  Wire.endTransmission();
  delay(1);
}