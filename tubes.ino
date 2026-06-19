#include <Arduino.h>
#include "struct.h"

static FILE uartout = {0};
static int uart_putchar(char c, FILE *stream) {
    Serial.write(c);
    return 0;
}

extern "C" void arduino_read_string(char* buffer, int max_len) {
    while (Serial.available() > 0 && (Serial.peek() == '\n' || Serial.peek() == '\r')) {
        Serial.read();
    }

    int idx = 0;
    while (true) {
        while (Serial.available() == 0) { }
        
        char c = Serial.read();
        
        if (c == '\n' || c == '\r') {
            break;
        }
        
        if (idx < max_len - 1) {
            buffer[idx++] = c;
        }
    }
    
    buffer[idx] = '\0';
}

void setup() {
    Serial.begin(9600);
    
    fdev_setup_stream(&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &uartout;

    delay(1000); 
    jalankan_sistem();
}

void loop() {
}
