/*
 * rxCsvExample.ino - Example Arduino sketch to read CSV data from UART
 * and display it on an I2C LCD.
 * This sketch uses the Adafruit LiquidCrystal library for I2C LCD control
 * Made by: [GPT-4]
 */

#include <Adafruit_LiquidCrystal.h>

/*
 * Initialize the LCD with the pins used: (rs, enable, d4, d5, d6, d7).
 * The parameter passed to the constructor (0) selects the default I2C address.
 */
Adafruit_LiquidCrystal lcd(0);

/*
 * Buffer size for storing incoming UART data.
 * The buffer should be large enough to hold a full CSV string.
 */
const int BUFFER_SIZE = 64;
char uartBuffer[BUFFER_SIZE];
uint8_t bufferIndex = 0;       /* Current index in UART buffer */
bool messageComplete = false;  /* Flag indicating full message received */

/*
 * setup() - Arduino standard initialization function.
 * Initializes LCD and UART communication.
 */
void setup() {
	lcd.begin(16, 2);         /* Configure the LCD for 16 columns and 2 rows */
	lcd.clear();              /* Clear any previous data on the display */
	Serial.begin(9600);       /* Start serial communication at 9600 baud */
}

/*
 * updateLCD() - Print a message on the LCD screen.
 * If the message is longer than 16 characters, it will wrap onto the second line.
 */
void updateLCD(String message) {
	lcd.clear();             /* Clear the display before writing */
	lcd.setCursor(0, 0);     /* Set cursor to the beginning of the first line */

	/*
	 * If message is too long for a single line,
	 * split and display across two lines.
	 */
	if (message.length() > 16) {
		String line1 = message.substring(0, 16);
		String line2 = message.substring(16, min(32, message.length()));
		lcd.print(line1);
		lcd.setCursor(0, 1);   /* Move to the second line */
		lcd.print(line2);
	} else {
		lcd.print(message);   /* Print directly if it fits on one line */
	}
}

/*
 * loop() - Arduino standard main loop function.
 * Continuously checks for new UART input and updates LCD if a message is complete.
 */
void loop() {
	/* Process all available characters from the serial buffer */
	while (Serial.available()) {
		char incomingChar = Serial.read();

		/*
		 * If newline received or buffer is full,
		 * terminate the string and flag as complete.
		 */
		if (incomingChar == '\n' || bufferIndex >= BUFFER_SIZE - 1) {
			uartBuffer[bufferIndex] = '\0';  /* Null-terminate the string */
			messageComplete = true;          /* Set flag to process message */
			bufferIndex = 0;                 /* Reset buffer index */
			break;
		} else {
			uartBuffer[bufferIndex++] = incomingChar;  /* Store character in buffer */
		}
	}

	/* If a complete message was received, display it */
	if (messageComplete) {
		String message = String(uartBuffer);
		updateLCD(message);
		messageComplete = false;  /* Reset flag after processing */
	}
}