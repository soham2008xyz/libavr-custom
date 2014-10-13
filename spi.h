/*
 * Multi Purpose SPI Header Library
 * ================================
 * Created by Saptarshi Hazra, Shashwata Gupta and Shoumik Ghosal
 *
 * Configurable parameters
 * =======================
 * 1. SPI_DORD
 * Set the data order (DEFAULT: MSB transmitted first)
 * 0 - MSB transmitted first
 * 1 - LSB transmitted first
 *
 * 2. SPI_CPOL
 * Set the clock polarity (DEFAULT: SCK is low when idle)
 * 0 - SCK low when idle
 * 1 - SCK high when idle
 *
 * 3. SPI_CPHA
 * Set the clock phase (DEFAULT: Data sampled at leading edge)
 * 0 - Data sampled on leading edge
 * 1 - Data sampled on trailing edge
 *
 * 4. SPI_MODE
 * Set the SPI Operation mode as Master or Slave (DEFAULT: Slave)
 * 0 - Slave mode
 * 1 - Master mode
 *
 * 5. SCK_FREQ
 * Set the frequency of the SPI clock as 1/N of the oscillator frequency
 * Allowed values of N are 2, 4, 8, 16, 32, 64, 128
 * Default frequency is f/4
 *
 * List of Compatible Devices
 * ==========================
 * 1. Atmega8
 *
 */

#ifndef _SPIPORTS_H_
/* No port definition has been included before
 * Assuming default port definitions for Atmega8
 */

#include "spiports-atmega8.h"
#endif // _SPIPORTS_H_

#ifndef _SPI_H_
#define _SPI_H_

/* Common initializations for both master and slave go here */
void _init_common() {

    /* Check and set the data order
     * If SPI_DORD is defined, use that value, else set data order as MSB transmitted first
     * @param SPCR - SPI Control Register
     * @param DORD - SPI Data Order
     */
    #ifndef SPI_DORD
    #define SPI_DORD 0
    #endif // SPI_DORD
    SPCR |= (SPI_DORD<<DORD);

    /* Check and set the clock polarity
     * If SPI_CPOL is defined, use that value, else set SCK as low when idle
     * @param SPCR - SPI Control Register
     * @param CPOL - SPI Clock Polarity
     */
    #ifndef SPI_CPOL
    #define SPI_CPOL 0
    #endif // SPI_CPOL
    SPCR |= (SPI_CPOL<<CPOL);

    /* Check and set the clock phase
     * If SPI_CPHA is defined, use that value, else set data to be sampled on leading edge of SCK
     * @param SPCR - SPI Control Register
     * @param CPHA - SPI Clock Phase
     */
    #ifndef SPI_CPHA
    #define SPI_CPHA 0
    #endif // SPI_CPHA
    SPCR |= (SPI_CPHA<<CPHA);

}

/* Initializations for master mode SPI */
void _init_master() {
    _init_common();

    /* The device shall be configured as a SPI master
     * MOSI, SCK, SS shall be output pins
     * MISO will be an input pin
     */
    SPIDDR |= ((0<<MISO) | (1<<MOSI) | (1<<SS) | (1<<SCK));

    /* SS will be set up as a normal output pin
     * SS is assumed to be connected to SS pin of slave, and is thus pulled high initially
     * You can use your own pins for slave select, and pull SS low in your code
     */
    SPIPORT |= (1<<SS);

    /* Enable the SPI peripheral by pulling SPI enable to high
     * @param SPCR - SPI Control Register
     * @param SPE - SPI Enable
     */
    SPCR |= (1<<SPE);

    /* Enable the master select by pulling it to high
     * @param SPCR - SPI Control Register
     * @param MSTR - SPI Master Select
     */
    SPCR |= (1<<MSTR);
}

/* Initializations for slave mode SPI */
void _init_slave() {

}

#endif // _SPI_H_
