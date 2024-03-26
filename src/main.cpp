#include <avr/io.h>
#include <util/delay.h>

#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

// Función para inicializar UART
void USART_init(void) {
    UBRR0H = (uint8_t)(BAUD_PRESCALLER >> 8);
    UBRR0L = (uint8_t)(BAUD_PRESCALLER);
    UCSR0B = (1 << TXEN0); // Habilita la transmisión
    UCSR0C = (3 << UCSZ00); // Configura el tamaño del carácter: 8 bits de datos
}

// Función para enviar un carácter a través de UART
void USART_send(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0))); // Espera a que el buffer de transmisión esté vacío
    UDR0 = data; // Transmite el carácter
}

int main(void) {
    // Inicializar UART
    USART_init();
    
    while (1) {
        // Enviar mensaje a través de UART
        USART_send('H');
        USART_send('o');
        USART_send('l');
        USART_send('a');
        USART_send('\n'); // Nueva línea
        _delay_ms(1000); // Espera 1 segundo
    }
}
