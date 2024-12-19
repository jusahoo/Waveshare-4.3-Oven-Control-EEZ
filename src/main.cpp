#include <Arduino.h>

/**
 * The example demonstrates how to port LVGL.
 *
 * ## How to Use
 *
 * To use this example, please firstly install `ESP32_Display_Panel` (including its dependent libraries) and
 * `lvgl` (v8.3.x) libraries, then follow the steps to configure them:
 *
 * 1. [Configure ESP32_Display_Panel](https://github.com/esp-arduino-libs/ESP32_Display_Panel#configure-esp32_display_panel)
 * 2. [Configure LVGL](https://github.com/esp-arduino-libs/ESP32_Display_Panel#configure-lvgl)
 * 3. [Configure Board](https://github.com/esp-arduino-libs/ESP32_Display_Panel#configure-board)
 *
 * ## Example Output
 *
 * ```bash
 * ...
 * Hello LVGL! V8.3.8
 * I am ESP32_Display_Panel
 * Starting LVGL task
 * Setup done
 * Loop
 * Loop
 * Loop
 * Loop
 * ...
 * ```
 */

/*


  If you want to use slaveid function to change the slaveid on the fly, you need to modify the ModbusMaster library (Or get the copy from my website)
  In ModbusMaster.h add at line 78
    void slaveid(uint8_t);
  In ModbusMaster.cpp add at line 75
    void ModbusMaster::slaveid(uint8_t slave)
     {
      _u8MBSlave = slave;
     }
*/
#include <lvgl.h>
#include <ESP_Panel_Library.h>
#include <ESP_IOExpander_Library.h>
#include <ui.h>
#include <vars.h>
#include <actions.h>
////////////////////////
// #include <WiFi.h>
#include <config.h>
#include <time.h>
#include <esp_sntp.h>

#include <TelnetStream.h>

#include <ElegantOTA.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);
#elif defined(ESP32)
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

WebServer server(80);
#endif

#include <ModbusMaster.h>

// instantiate ModbusMaster object
ModbusMaster node;

uint8_t arduSlaveAddr = 0x01;   // Arduino slave address
uint8_t moduleSlaveAddr = 0x02; // Slave address for the Waveshare slave module

uint16_t discreteOffset = 10000; // Offset for discrete register

uint16_t doorCloseRegister = 12; // Modbus discrete register to check if door is closed
bool doorClosed = false;

uint16_t lowOrHighReg = 11; // Modbus discrete register to check if relay is Low to On and Hig to off. 1 is low to on, 0 is high to on

uint16_t probeResReg = 1; // Temperature's probe resistance

// meassure resistance from probe tembperature
int probeRes = 0;

const uint16_t doorClosedReg = 12; // equivalent 10 10014 discrete address for master in base 1

// Oven Lights Parameters
const uint16_t lightReg = 4; // Register address for light

// Oven Fan Parameters

const uint16_t fanReg = 5;
bool fanIsOn = false;

// door Motor Parameters

const uint16_t doorMotorReg = 6;
bool doorIsLocked = false;

// Top Resistance Parameters

const uint16_t topResReg = 7;
bool topResIsOn = false;

// Bottom resistance Parameters

const uint16_t botResReg = 8;
bool botResIsOn = false;

// Communication Check Register
const uint16_t commCheckReg = 13;
bool commIsOk = false;

//Define relay type

bool LowToOnHighToOff = 1 ; //If true the relays closes on Low, opens on High

    int On =  0;
    int Off = 1;



uint32_t i = 0;

// Timers definition
unsigned long actualMillis = 0;
unsigned long prevMillis = 0;
unsigned long every100Millis = 100;
unsigned long prevEvery100Millis = 0;
unsigned long every500Millis = 5000;
unsigned long prevEvery500Millis = 0;
unsigned long everyOneSec = 1000;
unsigned long prevEveryOneSec = 0;
unsigned long everyFiveSec = 5000;
unsigned long prevEveryFiveSec = 0;
unsigned long everyTenSec = 10000;
unsigned long prevEveryTenSec = 0;
unsigned long everyTwoMin = 120000;
unsigned long prevEveryTwoMin = 0;
unsigned long everyHour = 3600000;
unsigned long prevEveryHour = 0;

int timerSet = 0; // store Timer Set
int prevTimerSet = -1;
int timerRem = 0; // store timer remaining
// int timerStart = 0; //Store the timer when start baking or broiling
int prevTimerRem = -0;
int timeStartClicked = 0;

// Temperature variables
int tempSetPoint = 0; // to store temperature setpoint
int prevTempSetPoint = -1;
int tempActual = 0; // variable to store de actual temperature

/// Flags definition

bool startClicked = false;
bool processProgram = false;
bool bLCtl = true; // backlight control

////////////////////////

// Extend IO Pin define
#define TP_RST 1
#define LCD_BL 2
#define LCD_RST 3
#define SD_CS 4
#define USB_SEL 5

// I2C Pin define
#define I2C_MASTER_NUM 0
#define I2C_MASTER_SDA_IO 8
#define I2C_MASTER_SCL_IO 9

#define RS485_RX_PIN 15
#define RS485_TX_PIN 16

// Redefine serial port name
#define RS485 Serial1

// instantiate ModbusMaster object

// Used Pins
const int LedPin = 13;  // Change that to match your led
const int TxenPin = -1; // -1 disables the feature, change that if you are using an RS485 driver, this pin would be connected to the DE and /RE pins of the driver.

ESP_IOExpander *expander = new ESP_IOExpander_CH422G(I2C_MASTER_NUM, ESP_IO_EXPANDER_I2C_CH422G_ADDRESS_000);

/**
/* To use the built-in examples and demos of LVGL uncomment the includes below respectively.
 * You also need to copy `lvgl/examples` to `lvgl/src/examples`. Similarly for the demos `lvgl/demos` to `lvgl/src/demos`.
 */
// #include <demos/lv_demos.h>
// #include <examples/lv_examples.h>

/* LVGL porting configurations */
#define LVGL_TICK_PERIOD_MS (2)
#define LVGL_TASK_MAX_DELAY_MS (500)
#define LVGL_TASK_MIN_DELAY_MS (1)
#define LVGL_TASK_STACK_SIZE (4 * 1024)
#define LVGL_TASK_PRIORITY (1)
#define LVGL_BUF_SIZE (ESP_PANEL_LCD_H_RES * 20)

ESP_Panel *panel = NULL;
SemaphoreHandle_t lvgl_mux = NULL; // LVGL mutex

#if ESP_PANEL_LCD_BUS_TYPE == ESP_PANEL_BUS_TYPE_RGB
/* Display flushing */
void lvgl_port_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  panel->getLcd()->drawBitmap(area->x1, area->y1, area->x2 + 1, area->y2 + 1, color_p);
  lv_disp_flush_ready(disp);
}
#else
/* Display flushing */
void lvgl_port_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  panel->getLcd()->drawBitmap(area->x1, area->y1, area->x2 + 1, area->y2 + 1, color_p);
}

bool notify_lvgl_flush_ready(void *user_ctx)
{
  lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
  lv_disp_flush_ready(disp_driver);
  return false;
}
#endif /* ESP_PANEL_LCD_BUS_TYPE */

#if ESP_PANEL_USE_LCD_TOUCH
/* Read the touchpad */
void lvgl_port_tp_read(lv_indev_drv_t *indev, lv_indev_data_t *data)
{
  panel->getLcdTouch()->readData();

  bool touched = panel->getLcdTouch()->getTouchState();
  if (!touched)
  {
    data->state = LV_INDEV_STATE_REL;
  }
  else
  {
    TouchPoint point = panel->getLcdTouch()->getPoint();

    data->state = LV_INDEV_STATE_PR;
    /*Set the coordinates*/
    data->point.x = point.x;
    data->point.y = point.y;

    Serial.printf("Touch point: x %d, y %d\n", point.x, point.y);
  }
}
#endif

void lvgl_port_lock(int timeout_ms)
{
  const TickType_t timeout_ticks = (timeout_ms < 0) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);
  xSemaphoreTakeRecursive(lvgl_mux, timeout_ticks);
}

void lvgl_port_unlock(void)
{
  xSemaphoreGiveRecursive(lvgl_mux);
}

void lvgl_port_task(void *arg)
{
  Serial.println("Starting LVGL task");

  uint32_t task_delay_ms = LVGL_TASK_MAX_DELAY_MS;
  while (1)
  {
    // Lock the mutex due to the LVGL APIs are not thread-safe
    lvgl_port_lock(-1);
    task_delay_ms = lv_timer_handler();
    // Release the mutex
    lvgl_port_unlock();
    if (task_delay_ms > LVGL_TASK_MAX_DELAY_MS)
    {
      task_delay_ms = LVGL_TASK_MAX_DELAY_MS;
    }
    else if (task_delay_ms < LVGL_TASK_MIN_DELAY_MS)
    {
      task_delay_ms = LVGL_TASK_MIN_DELAY_MS;
    }
    vTaskDelay(pdMS_TO_TICKS(task_delay_ms));
  }
}

////////////////////////////////

// Replace with your network credentials
const char *wifiSSID = SECRET_SSID;
const char *wifiPASS = SECRET_PASS;
const char *wifiHostName = "esp32-oven-ctl";

const int wifiMaxRetries = 5;
int wifiRetries = 0;
unsigned long wifiNoOkTimer = 0;        // Timer to control the time Wifi is not connected
unsigned long wifiMaxNoOkTimer = 60000; // Max timer with Not Connected then TurnOff Burner
unsigned long previousWifiNoOkTimer = 0;

int wifiStatus = 0;

const char *ntpServer1 = "pool.ntp.org";
const char *ntpServer2 = "time.nist.gov";
const long gmtOffset_sec = -14400;
const int daylightOffset_sec = -0;

const int minTemp = CONFIG_MinTemp;
const int maxTemp = CONFIG_MaxTemp;
const int stepTemp = CONFIG_StepTemp;

// lv_obj_t *mbox01 ;

/*
void actualTime(){
      while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  // The formattedDate comes with the following format:
  // 2018-05-28T16:00:13Z
  // We need to extract date and time
  formattedDate = timeClient.getFormattedTime();
  Serial.println(formattedDate);

  // Extract date
  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
  Serial.print("DATE: ");
  Serial.println(dayStamp);
  // Extract time
  timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);
  Serial.print("HOUR: ");
  Serial.println(timeStamp);
}
*/
void printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("No time available (yet)");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

// Callback function (gets called when time adjusts via NTP)
void timeavailable(struct timeval *t)
{
  Serial.println("Got time adjustment from NTP!");
  printLocalTime();
}

void setupTime()
{
  // set notification call-back function
  sntp_set_time_sync_notification_cb(timeavailable);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
}

void printWifiStatus()
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  String ipTxt = WiFi.localIP().toString();
  lv_label_set_text_fmt(objects.ip_addr_lbl, "%s", ipTxt.c_str());
}

void connectWifi()
{
  // attempt to connect to WiFi network:
  wifiRetries = 0;
  Serial.println("connectWifi function");

  while ((wifiStatus != WL_CONNECTED) && (wifiRetries <= wifiMaxRetries))
  // while (((wifiStatus != 3) != (wifiStatus != 6)) && (wifiRetries <= wifiMaxRetries))

  {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(wifiSSID); // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    WiFi.setHostname(wifiHostName);
    wifiStatus = WiFi.begin(wifiSSID, wifiPASS);
    delay(1000);
    printWifiStatus();
    wifiRetries++;
    Serial.println(wifiRetries);
    Serial.println(wifiStatus);
  }
  printWifiStatus();
}

void FillDateTimeLbls()
{
  char dateL[12];

  time_t rawtime;
  struct tm *timeinfo;
  time(&rawtime);

  timeinfo = localtime(&rawtime);
  // char buffer[80];

  // strftime(dateL, 80, "%Y%m%d %H:%M:%S",timeinfo);
  strftime(dateL, 12, "%a, %b %d", timeinfo);
  lv_label_set_text_fmt(objects.date_lbl, dateL);
  strftime(dateL, 12, "  %I:%M %p", timeinfo);
  lv_label_set_text_fmt(objects.time_lbl, dateL);
  // Serial.println(dateL);
  sleep(1);
}

void SetupInitialTemp()
{
  set_var_max_temp_set_point(maxTemp);
  set_var_min_temp_set_point(minTemp);
  set_var_step_temp_set_point(stepTemp);
  set_var_temp_set_point(minTemp);
}

void FillTempSetPointLbl()
{
  char setP[3];
  int set = get_var_temp_set_point();
  Serial.print("SetPoint = ");
  Serial.println(set);
  sprintf(setP, "%i", set);
  lv_spinbox_set_value(objects.temp_set_point_spin, set);

  // lv_label_set_text(objects.temp_set_point_lbl , setP);
}

void ReadTempSetPoint()
{
  tempSetPoint = get_var_temp_set_point();

  if (tempSetPoint != prevTempSetPoint)
  {
    // Serial.println(tempSetPoint);
    FillTempSetPointLbl();
    prevTempSetPoint = tempSetPoint;
  }
}

void ReadTimerSet()
{
  timerSet = get_var_timer_set_min();
  if (timerSet != prevTimerSet)
  {
    int32_t t = timerSet;

    lv_spinbox_set_value(objects.timer_set_spn, t);
    prevTimerSet = timerSet;
  }
}

void CheckTimerRem()
{
  timerSet = get_var_timer_set_min();

  if (processProgram)
  {
    int previousTR = timerRem;

    timerRem = timerSet - int((actualMillis - timeStartClicked) / 60000);

    if (timerRem > 0)
    {
      // Serial.print("Timer Remaining= ");
      // Serial.println(timerRem);
    }
    else
    {
      timerRem = 0;
    }
    if ((timerRem > 0) && (timerRem != previousTR))
    {
      char t[3];
      sprintf(t, "%i", timerRem);
      lv_label_set_text(objects.timer_rem_lbl, t);
    }
    else
    {
      lv_label_set_text(objects.timer_rem_lbl, "___");
    }
    if ((timerRem = 0) && (processProgram == true))
    {
      Serial.println("Timer ended");
      //  End the programed process and turn off all resistances  and accesories
      // set_var_timer_set_min(0);
    }
  }
}
/*
void displayMessageBox(){
              // ErrorMessagesBox
            lv_obj_t *obj = lv_msgbox_create(parent_obj);
            objects.error_messages_box = obj;
            lv_obj_set_pos(obj, 292, 251);
            lv_obj_set_size(obj, 180, 100);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
}
*/

void CreateMsgBox(char titulo[10], char mensaje[50])
{
  lv_obj_t *mbox01 = lv_msgbox_create(NULL, titulo, mensaje, 0, true);
  // mbox01 = lv_msgbox_create(NULL, titulo, mensaje, 0, true);

  lv_obj_set_pos(mbox01, LV_PCT(15), LV_PCT(15));
  lv_obj_set_size(mbox01, LV_PCT(70), LV_PCT(70));
  lv_obj_set_style_align(mbox01, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(mbox01, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
};

void StartBtnStyle()
{
  bool p = processProgram;

  if (p == false)
  {
    lv_obj_set_style_bg_color(objects.start_btn, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(objects.start_btn_lbl, "Start");
  }
  else
  {
    lv_obj_set_style_bg_color(objects.start_btn, lv_color_hex(0xfff33121), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(objects.start_btn_lbl, "Stop");
  }
}

void CheckStartClicked()
{
  bool clicked = get_var_start_clicked();
  bool programStopped = false;
  // timerSet = get_var_timer_set_min();

  // Serial.print(clicked);
  // Serial.print("timerRem:  ");
  // Serial.println(timerRem);
  if (clicked == true)
  {

    Serial.println("Clicked");
    Serial.println(timerSet);

    if ((timerRem >= 0) && (processProgram == true))
    {
      processProgram = false;
      programStopped = true;
      clicked = false;
      Serial.println("Process stoped");
    }

    if (timerSet == 0)
    {
      processProgram = false;
      clicked = false;
      Serial.println("Timer Set = 0");

      CreateMsgBox("Error", "Timer should be > 0.");
    }

    if ((timerSet > 0) && (processProgram == false) && (programStopped == false))
    {
      processProgram = true;
      timeStartClicked = int(actualMillis / 60000);
      timerRem = timerSet - int((actualMillis - timeStartClicked) / 60000);
      Serial.println("Process of program true");
      delay(1);
    }
  }
  StartBtnStyle();
  // Serial.print("Process of Program: ");
  // Serial.println(processProgram);

  if (programStopped)
  {
    set_var_timer_set_min(0);
    set_var_timer_remain_min(0);
    timerRem = 0;
    CheckTimerRem();
  }

  set_var_start_clicked(false);
  delay(1);
}

////////////////////////////

void cntlRemPin(u_int8_t remoteID, uint16_t pinNum, bool state)
{
}

void WriteCoilToSlave(uint8_t slaveAddr = 0x01, uint16_t regAddress = 13, int value = 1)
{

  uint8_t result;
  // int result;
  // uint16_t registerAddress = 0x0002    //Register equivalent to Arduino pin number
  node.begin(arduSlaveAddr, RS485);
  result = node.writeSingleCoil(regAddress, value);
  Serial.println(result);
  if (result == node.ku8MBSuccess)
  {
    Serial.println(result);
    Serial.print("Coil written OK: ");
    Serial.println(regAddress);
    TelnetStream.println("Coil written OK");
  }
  else
  {
    Serial.println(result);
    Serial.print("Coil Write ERROR:  ");
    Serial.println(regAddress);
    TelnetStream.println("Coil Write ERROR");
  }
}

bool readDiscreteReg(uint8_t slaveAddr, uint16_t registro)
{

  node.begin(slaveAddr, RS485);
  bool res = false;

  uint8_t result = node.readDiscreteInputs(registro, 1);

  TelnetStream.print("Discrete Read = ");
  TelnetStream.println(node.getResponseBuffer(0));
  Serial.print("Discrete Read = ");
  Serial.println(node.getResponseBuffer(0));

  if (result = 1)
  {
    res = true;
  }
  else if (result = 0)
  {
    res = false;
  }
  else
  {
    Serial.println("Discrete Read error, program stoped");
    TelnetStream.println("Discrete Read error, program stoped");

    processProgram = false;
  }

  return res;

  // uint16_t registerAddress = 0x0002    //Register equivalent to Arduino pin number
}

int readHoldingReg(uint8_t slaveAddr, uint16_t registro)
{

  int res = 0;
  node.begin(slaveAddr, RS485);

  uint8_t result; // Variable to store the result of Modbus operations

  // Read 2 holding registers starting at address 0x0000
  // This function sends a Modbus request to the slave to read the registers
  result = node.readHoldingRegisters(registro, 1);

  // If the read is successful, process the data
  if (result == node.ku8MBSuccess)
  {
    // Get the response data from the response buffer

    TelnetStream.print("Holding Read Reg : ");
    TelnetStream.print(registro);
    TelnetStream.print("  data = ");
    TelnetStream.println(node.getResponseBuffer(0));

    Serial.print("Holding Read Reg : ");
    Serial.print(registro);
    Serial.print("  data = ");
    Serial.println(node.getResponseBuffer(0));

    res = node.getResponseBuffer(0);
  }
  else
  {
    // Print an error message if the read fails
    Serial.print("Modbus read failed Reg: ");
    Serial.print(registro);
    Serial.print(" result code: ");
    Serial.println(result, HEX); // Print the error code in hexadecimal format
    res = 0;
  }

  return res;
}

void CommCheck()
{
  int i = 0;
  i = readDiscreteReg(1, commCheckReg);

  Serial.printf("CommCheck i  = %i\n", i);

  if (i == 1){
    commIsOk = true;
    Serial.println("Comm is Ok");
  } else {
    commIsOk = false;
    Serial.println("Comm Lost");
  }
}

void TurnLight(bool estado){
  if (commIsOk){
  WriteCoilToSlave(arduSlaveAddr, lightReg, estado);
  }
}

///////////////

void setup()
{
  Serial.begin(38400); /* prepare for possible serial debug */
  delay(1000);

  Serial2.begin(115200, SERIAL_8N1, 15, 16);

  String LVGL_Arduino = "Hello LVGL! ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

  Serial.println(LVGL_Arduino);
  Serial.println("I am ESP32_Display_Panel");

  panel = new ESP_Panel();

  /* Initialize LVGL core */
  lv_init();

  /* Initialize LVGL buffers */
  static lv_disp_draw_buf_t draw_buf;
  /* Using double buffers is more faster than single buffer */
  /* Using internal SRAM is more fast than PSRAM (Note: Memory allocated using `malloc` may be located in PSRAM.) */
  uint8_t *buf = (uint8_t *)heap_caps_calloc(1, LVGL_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_INTERNAL);
  assert(buf);
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, LVGL_BUF_SIZE);

  /* Initialize the display device */
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  /* Change the following line to your display resolution */
  disp_drv.hor_res = ESP_PANEL_LCD_H_RES;
  disp_drv.ver_res = ESP_PANEL_LCD_V_RES;
  disp_drv.flush_cb = lvgl_port_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

#if ESP_PANEL_USE_LCD_TOUCH
  /* Initialize the input device */
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = lvgl_port_tp_read;
  lv_indev_drv_register(&indev_drv);
#endif
  /* Initialize bus and device of panel */
  panel->init();
#if ESP_PANEL_LCD_BUS_TYPE != ESP_PANEL_BUS_TYPE_RGB
  /* Register a function to notify LVGL when the panel is ready to flush */
  /* This is useful for refreshing the screen using DMA transfers */
  panel->getLcd()->setCallback(notify_lvgl_flush_ready, &disp_drv);
#endif

  /**
   * These development boards require the use of an IO expander to configure the screen,
   * so it needs to be initialized in advance and registered with the panel for use.
   *
   */
  Serial.println("Initialize IO expander");
  /* Initialize IO expander */
  // ESP_IOExpander *expander = new ESP_IOExpander_CH422G(I2C_MASTER_NUM, ESP_IO_EXPANDER_I2C_CH422G_ADDRESS_000, I2C_MASTER_SCL_IO, I2C_MASTER_SDA_IO);
  //  ESP_IOExpander *expander = new ESP_IOExpander_CH422G(I2C_MASTER_NUM, ESP_IO_EXPANDER_I2C_CH422G_ADDRESS_000);
  expander->init();
  expander->begin();
  expander->multiPinMode(TP_RST | LCD_BL | LCD_RST | SD_CS | USB_SEL, OUTPUT);
  expander->multiDigitalWrite(TP_RST | LCD_BL | LCD_RST | SD_CS, HIGH);

  // Turn off backlight
  // expander->digitalWrite(USB_SEL, LOW);
  expander->digitalWrite(USB_SEL, LOW);
  /* Add into panel */
  panel->addIOExpander(expander);

  /* Start panel */
  panel->begin();

  /* Create a task to run the LVGL task periodically */
  lvgl_mux = xSemaphoreCreateRecursiveMutex();
  xTaskCreate(lvgl_port_task, "lvgl", LVGL_TASK_STACK_SIZE, NULL, LVGL_TASK_PRIORITY, NULL);

  /* Lock the mutex due to the LVGL APIs are not thread-safe */
  lvgl_port_lock(-1);

  ui_init();

  /* Release the mutex */
  lvgl_port_unlock();

  //////////////////////////////////////////////
  // attempt to connect to WiFi network:
  Serial.println("going to connetwifi function");
  connectWifi();
  setupTime();
  //  actualTime();
  SetupInitialTemp();
  // nitialize timerSet
  set_var_timer_set_min(0);

  /////////////////////////////////////////
  TelnetStream.begin();
  server.on("/", []()
            { server.send(200, "text/plain", "Hi! This is ElegantOTA Demo."); });

  ElegantOTA.begin(&server); // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");

  // Initialize 485 device
  RS485.begin(38400, SERIAL_8N1, RS485_RX_PIN, RS485_TX_PIN);
  while (!RS485)
  {
    delay(10); // Wait for initialization to succeed
  }

  // Define relay type
  LowToOnHighToOff  = readDiscreteReg(1, lowOrHighReg);
  Serial.printf("LowToOnHighToOff = %i\n", LowToOnHighToOff);
  TelnetStream.printf("LowToOnHighToOff = %i\n", LowToOnHighToOff);

  if (LowToOnHighToOff == 1){
     On  = 0;
     Off = 1;
  } else {
     On  =  1;
     Off  = 0;
  }



}

void loop()
{
  actualMillis = millis();
  server.handleClient();
  ElegantOTA.loop();

  // run every 100 millia
  if (actualMillis - prevEvery100Millis >= every100Millis)
  {

    ReadTempSetPoint();

    ReadTimerSet();

    CheckTimerRem();

    CheckStartClicked();
    StartBtnStyle();

    prevEvery100Millis = actualMillis;
  }

  // Run every 500 Millis
  if (actualMillis - prevEvery500Millis >= every500Millis)
  {
    FillDateTimeLbls();

    prevEvery500Millis = actualMillis;
  }

  // Run every 5 seconds
  if (actualMillis - prevEveryFiveSec >= everyFiveSec)
  {

    CommCheck();

/*
    for (uint8_t i = 4; 13; i++)
    {
      WriteCoilToSlave(1, i, 0);
      readDiscreteReg(1, i);
      delay(50);
      WriteCoilToSlave(1, i, 1);
      readDiscreteReg(1, i);
      delay(50);
      readHoldingReg(1, 1);
    }
  */

    // TelnetStream.println("Inside Loop");
    /*
      TelnetStream.println(WiFi.localIP());
      if (bLCtl) {
        expander->digitalWrite(LCD_BL, LOW);
        cntlRemPin(1, 13, false);
        bLCtl = false;
        WriteCoilToSlave(1, 13, 0);
      } else {
        expander->digitalWrite(LCD_BL, HIGH);
        cntlRemPin(1,13,true);
        bLCtl = true;
        WriteCoilToSlave(1, 13, 1);

      }
    */
    // Serial.println(readDiscreteReg(0x01, doorCloseRegister + discreteOffset));
    // Serial.print("Low to On: ");
    // Serial.println( Serial.println(readDiscreteReg(0x01, lowOrHighReg + discreteOffset)));

    /*
        WriteDigiPin(2, true);
        delay(2000);
        WriteDigiPin(2, false);
        delay(1000);
    */
    // Write message to the slave

    prevEveryFiveSec = actualMillis;
  }

  ///////

  // printLocalTime();  // it will take some time to sync time :)
  delay(1);
}
