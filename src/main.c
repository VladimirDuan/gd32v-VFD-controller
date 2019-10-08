/*!
    \file  main.c
    \brief running led
    
    \version 2019-6-5, V1.0.0, firmware for GD32VF103
*/

/*
    Copyright (c) 2019, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "gd32vf103.h"
#include "gd32v103v_eval.h"
#include "systick.h"
#include <stdio.h>
#include <string.h>
#include "spi.h"


uint16_t calculate_segments_14(uint8_t character);
uint16_t display_seg(unsigned char c);
uint16_t display_string(unsigned char* str);

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    /* peripheral clock enable */
    rcu_config();
    rcu_periph_clock_enable(RCU_USART0);
    /* GPIO configure */
    gpio_config();

    /* connect port to USARTx_Tx */
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    /* connect port to USARTx_Rx */
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

    
    /* USART configure */
    usart_deinit(USART0);
    usart_baudrate_set(USART0, 115200U);
    usart_word_length_set(USART0, USART_WL_8BIT);
    usart_stop_bit_set(USART0, USART_STB_1BIT);
    usart_parity_config(USART0, USART_PM_NONE);
    usart_hardware_flow_rts_config(USART0, USART_RTS_DISABLE);
    usart_hardware_flow_cts_config(USART0, USART_CTS_DISABLE);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_enable(USART0);

    /* SPI configure */
    spi_config();

    spi_enable(SPI0);
    stb_high();
    
    delay_1ms(2000);

    GPIO_BOP(GPIOB) = GPIO_PIN_0; // ROYER EN
    
    delay_1ms(1000);

    
    stb_low();
    spi_send(0b01000000);
    stb_high();

    stb_low();
    spi_send(0b11000000);

    display_seg(' ');
    display_seg('D');
    display_seg('L');
    display_seg('R');
    display_seg('O');
    display_seg('W');
    display_seg(' ');
    display_seg('O');
    display_seg('L');
    display_seg('L');
    display_seg('E');
    display_seg('H');

    stb_high();

    stb_low();
    spi_send(0b00001011);   // 12 digits, 16 segments
    stb_high();

    stb_low();
    spi_send(0b10001111);   // display on
    stb_high();

    while (1)
    {
        //delay_1ms(2000);
        display_string("            ");
        display_string("D           ");
        display_string("LD          ");
        display_string("RLD         ");
        display_string("ORLD        ");
        display_string("WORLD       ");
        display_string(" WORLD      ");
        display_string("O WORLD     ");
        display_string("LO WORLD    ");
        display_string("LLO WORLD   ");
        display_string("ELLO WORLD  ");
        display_string("HELLO WORLD ");
        display_string(" HELLO WORLD");
        display_string("  HELLO WORL");
        display_string("   HELLO WOR");
        display_string("    HELLO WO");
        display_string("     HELLO W");
        display_string("      HELLO ");
        display_string("       HELLO");
        display_string("        HELL");
        display_string("         HEL");
        display_string("          HE");
        display_string("           H");
        display_string("            ");
        display_string("           H");
        display_string("          HE");
        display_string("         HEL");
        display_string("        HELL");
        display_string("       HELLO");
        display_string("      HELLO ");
        display_string("     HELLO W");
        display_string("    HELLO WO");
        display_string("   HELLO WOR");
        display_string("  HELLO WORL");
        display_string(" HELLO WORLD");
        display_string("HELLO WORLD ");
        display_string("ELLO WORLD  ");
        display_string("LLO WORLD   ");
        display_string("LO WORLD    ");
        display_string("O WORLD     ");
        display_string(" WORLD      ");
        display_string("WORLD       ");
        display_string("ORLD        ");
        display_string("RLD         ");
        display_string("LD          ");
        display_string("D           ");
        display_string("            ");

            // TODO: fetch real information from pc by usb-hid.
        display_string("** CPU-41 **");
        delay_1ms(2000);
        display_string("** MEM-28 **");
        delay_1ms(2000);


        /*
        delay_1ms(500);
        //GPIO_BC(GPIOB) = GPIO_PIN_0; // ROYER DEN   
        delay_1ms(1000);
        
        display_string("VFD ENABLED");
        GPIO_BOP(GPIOB) = GPIO_PIN_0; // ROYER EN   
        */
    }
}

/* retarget the C library printf function to the USART */
int _put_char(int ch)
{
    usart_data_transmit(USART0, (uint8_t) ch );
    while ( usart_flag_get(USART0, USART_FLAG_TBE)== RESET){
    }

    return ch;
}

uint16_t display_seg(unsigned char c)
{
    uint16_t i = calculate_segments_14(c);
    
    spi_send(i&0xff);
    spi_send((i>>8)&0xff);
    spi_send(0b00000000);
}

uint16_t display_string(unsigned char* str)
{
    unsigned char newstr[12];
    strcpy(newstr,str);
    for(uint8_t i = 0; i < 12; i++)
    {
        if(newstr[i] == 0)
        {
            newstr[i] = ' ';
        }
    }
    stb_low();
    spi_send(0b11000000);

    display_seg(newstr[11]);
    display_seg(newstr[10]);
    display_seg(newstr[9]);
    display_seg(newstr[8]);
    display_seg(newstr[7]);
    display_seg(newstr[6]);
    display_seg(newstr[5]);
    display_seg(newstr[4]);
    display_seg(newstr[3]);
    display_seg(newstr[2]);
    display_seg(newstr[1]);
    display_seg(newstr[0]);

    stb_high();
        delay_1ms(100);
}

