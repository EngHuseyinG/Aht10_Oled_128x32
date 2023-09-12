#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;


#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 32  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES 10  // Number of snowflakes in the animation example

#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16



static const unsigned char PROGMEM  wifi_icon[] =
{
	0b00000000, 0b00000000, //                 
	0b00000111, 0b11100000, //      ######     
	0b00011111, 0b11111000, //    ##########   
	0b00111111, 0b11111100, //   ############  
	0b01110000, 0b00001110, //  ###        ### 
	0b01100111, 0b11100110, //  ##  ######  ## 
	0b00001111, 0b11110000, //     ########    
	0b00011000, 0b00011000, //    ##      ##   
	0b00000011, 0b11000000, //       ####      
	0b00000111, 0b11100000, //      ######     
	0b00000100, 0b00100000, //      #    #     
	0b00000001, 0b10000000, //        ##       
	0b00000001, 0b10000000, //        ##       
	0b00000000, 0b00000000, //                 
	0b00000000, 0b00000000, //                 
	0b00000000, 0b00000000, //                 
};

const unsigned char mobile_icon[] =
{
	0b00000000, 0b00000000, //                 
	0b00000000, 0b00110000, //           ##    
	0b00000000, 0b00110000, //           ##    
	0b00001111, 0b11111000, //     #########   
	0b00001111, 0b11111000, //     #########   
	0b00001100, 0b00011000, //     ##     ##   
	0b00001100, 0b00011000, //     ##     ##   
	0b00001100, 0b00011000, //     ##     ##   
	0b00001100, 0b00011000, //     ##     ##   
	0b00001111, 0b11111000, //     #########   
	0b00001111, 0b11111000, //     #########   
	0b00001111, 0b11111000, //     #########   
	0b00001111, 0b11111000, //     #########   
	0b00001111, 0b11111000, //     #########   
	0b00001111, 0b11111000, //     #########   
	0b00001111, 0b11111000, //     #########   
};

const unsigned char bulb_on[] =
{
	0b00000000, 0b00000000, //                 
	0b00100011, 0b11100010, //   #   #####   # 
	0b00010100, 0b00010100, //    # #     # #  
	0b00001000, 0b00001000, //     #       #   
	0b00010000, 0b00000100, //    #         #  
	0b00010000, 0b00000100, //    #         #  
	0b00010000, 0b00000100, //    #         #  
	0b00010000, 0b00000100, //    #         #  
	0b00010000, 0b00000100, //    #         #  
	0b00001000, 0b00001000, //     #       #   
	0b00010100, 0b00010100, //    # #     # #  
	0b00100011, 0b11100010, //   #   #####   # 
	0b00000010, 0b00100000, //       #   #     
	0b00000011, 0b11100000, //       #####     
	0b00000010, 0b00100000, //       #   #     
	0b00000011, 0b11100000, //       #####     
};

const unsigned char bulb_off[] =
{
	0b00000000, 0b00000000, //                 
	0b00000011, 0b11100000, //       #####     
	0b00000111, 0b11110000, //      #######    
	0b00001111, 0b11111000, //     #########   
	0b00011111, 0b11111100, //    ###########  
	0b00011111, 0b11111100, //    ###########  
	0b00011111, 0b11111100, //    ###########  
	0b00011111, 0b11111100, //    ###########  
	0b00011111, 0b11111100, //    ###########  
	0b00001111, 0b11111000, //     #########   
	0b00000100, 0b00010000, //      #     #    
	0b00000011, 0b11100000, //       #####     
	0b00000010, 0b00100000, //       #   #     
	0b00000011, 0b11100000, //       #####     
	0b00000010, 0b00100000, //       #   #     
	0b00000011, 0b11100000, //       #####     
};









void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }

    if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 or AHT20 found");



  // Clear the buffer
  display.clearDisplay();



  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);

  display.setTextSize(2);  // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("KAS Proje");
  display.println("Otomasyon");
  display.display();

  delay(2000);

  display.clearDisplay();

  display.drawBitmap(0, 0, wifi_icon, 16, 16, 1);
  display.drawBitmap(20, 0, mobile_icon, 16, 16, 1);
   display.drawBitmap(40, 0, bulb_on, 16, 16, 1);
    display.drawBitmap(60, 0, bulb_off, 16, 16, 1);




  display.display();
  delay(1000);
}

void loop() {
    sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  display.clearDisplay();
    display.drawBitmap(0, 0, wifi_icon, 16, 16, 1);
  display.drawBitmap(20, 0, mobile_icon, 16, 16, 1);
   display.drawBitmap(40, 0, bulb_on, 16, 16, 1);
    display.drawBitmap(60, 0, bulb_off, 16, 16, 1);
    display.setTextSize(1);  // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0, 25);
  display.print(String(temp.temperature) + " C");
  
  display.setCursor(64, 25);
  display.print(String(humidity.relative_humidity) + " %");
 
 display.display();
  delay(1000);
}
