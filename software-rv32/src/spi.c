#include "spi.h"

/*!
    \brief      configure the SPI peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void spi_config(void)
{
    spi_parameter_struct spi_init_struct;
    /* deinitilize SPI and the parameters */
    spi_i2s_deinit(SPI0);
    spi_struct_para_init(&spi_init_struct);

    /* configure SPI0 parameter */
    spi_init_struct.trans_mode = SPI_TRANSMODE_FULLDUPLEX;
    spi_init_struct.device_mode = SPI_MASTER;
    spi_init_struct.frame_size = SPI_FRAMESIZE_8BIT;
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
    spi_init_struct.nss = SPI_NSS_SOFT;
    spi_init_struct.prescale = SPI_PSC_16;
    spi_init_struct.endian = SPI_ENDIAN_LSB; // LSB First.
    spi_init(SPI0, &spi_init_struct);
}

/*!
    \brief      configure the GPIO peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gpio_config(void)
{
    /* SPI0 GPIO config: SCK/PA5, MISO/PA6, MOSI/PA7 */
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5 | GPIO_PIN_7);
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
    //gpio_pin_remap_config(GPIO_SPI0_REMAP, ENABLE);

    /* SPI0 GPIO config: CS/PA4 USBEN/PA0*/
    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_4 | GPIO_PIN_0);

    /* PB0/VFDEN */
    gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
}

/*!
    \brief      configure different peripheral clocks
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_config(void)
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_AF);
    rcu_periph_clock_enable(RCU_SPI0);
}

uint8_t spi_send(uint8_t data)
{
    while (RESET == spi_i2s_flag_get(SPI0, SPI_FLAG_TBE))
        ;
    spi_i2s_data_transmit(SPI0, data);
    return 0; //TODO: should return duplex receive value.
}

uint8_t stb_high(void)
{
    delay_1us(10);
    GPIO_BOP(GPIOA) = GPIO_PIN_4;
    delay_1us(10);
}

uint8_t stb_low(void)
{
    delay_1us(10);
    GPIO_BC(GPIOA) = GPIO_PIN_4;
    delay_1us(10);
}
