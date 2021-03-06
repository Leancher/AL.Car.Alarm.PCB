#include "board/board.h"


void board_init()
{
	sensor_ignition_key_enable();
	relay_ignition_set_state(0);
	relay_starter_set_state(0);
	board_button_enable();
	//board_led_set_state(1);
	remote_running=0;
	number_minutes_work=0;
	current_state=ENGINE_STOP;
	_delay_ms(3);
	setbit(UCSR1B,RXCIE1,1);
	sei();
}

ISR(USART1_RX_vect)
{
	cli();
	sserial_poll_uart(UART_485);
	sei();
}

ISR(BADISR_vect)
{
	while(1);
}

void sserial_process_request(unsigned char portindex)
{
	process_command_control_engine();
}

int main(void)
{
	wdt_enable(WDTO_4S);
	uart_init_withdivider(UART_485,UBRR_VALUE);
	board_init();
    while (1) 
    {
		wdt_reset();
	 	//////get_state_start_button();
		//////switch_led();

		process_running_engine();
		_delay_ms(1);
    }
}

