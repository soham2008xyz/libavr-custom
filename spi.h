/*
 * Multi Purpose SPI Header Library
 * ================================
 * Created by Saptarshi Hazra, Shashwata Gupta and Shoumik Ghosal
 *
 * A. Instructions
 * ===============
 * 1. A list of compatible devices with this library is contained in Section C below.
 *    If your device is not contained in the list, you may go ahead and give this library a go.
 *    Or if you're feeling adventurous, go ahead and look up the datasheet for your device, and
 *    then modify spiports-generic.h to suit your needs.
 *
 * 2. A lot of configurable parameters for this library are contained in Section B below.
 *    The syntax for configuring any parameter is:
 *    #define PARAMETER VALUE
 *    NOTE: Make sure all definitions are complete before you include spi.h in your code.
 *    Mis-configuring these parameters may cause the library to stop working, so its best to
 *    stick to the defaults unless you know what you're doing.
 *
 * 3. You must include the specific port definitions for your device before you include this library.
 *    The port definitions are specified as apiports-devicename.h
 *
 * B. Configurable parameters
 * ==========================
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
 * 6. SPI_MAX_STRING_LENGTH
 * Set the maximum transmissible length of a string in a single transmission
 * Default value is 255
 *
 * C. List of Compatible Devices
 * =============================
 * 1. Atmega8
 *
 */

#ifndef _SPIPORTS_H_
/* No port definition has been included before
 * Assuming default port definitions for generic device
 */
#define _SPIPORTS_H_

/* Initial configuration of ports go here
 * @param SPIPORT - The variable used to mask the SPI port, per device
 * @param SPIDDR - The variable used the mask the SPI Data Direction Register, per device
 * @param SS - The variable used to mask the per-device slave select
 * @param MOSI - The variable used to mask the per-device master-out, slave in
 * @param MISO - The variable used to mask the per-device master-in, slave out
 * @param SCK - The variable used to mask the per-device serial clock
 */

#define SPIPORT PORTB
#define SPIDDR DDRB

#define SS PB2
#define MOSI PB3
#define MISO PB4
#define SCK PB5

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

    /* Enable the SPI peripheral by pulling SPI enable to high
     * @param SPCR - SPI Control Register
     * @param SPE - SPI Enable
     */
    SPCR |= (1<<SPE);
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

    /* Enable the master select by pulling it to high
     * @param SPCR - SPI Control Register
     * @param MSTR - SPI Master Select
     */
    SPCR |= (1<<MSTR);
}

/* Initializations for slave mode SPI */
void _init_slave() {
    _init_common();

    /* The device shall be configured as a SPI slave
     * MOSI, SCK, SS shall be input pins
     * MISO will be an output pin
     */
    SPIDDR |= ((1<<MISO) | (0<<MOSI) | (0<<SS) | (0<<SCK));

    /* Enable the slave select by pulling it to low
     * @param SPCR - SPI Control Register
     * @param MSTR - SPI Master Select
     */
    SPCR |= (0<<MSTR);
}

/* Function to write a single character to the data register
 * @param data - 1 byte of character data to be written to the SPI data register
 * @param SPDR - SPI data register
 */
void _spi_write(unsigned char data) {
    /* Dummy character to hold the data returned by SPI
     * Since SPI is always full duplex
     */
    unsigned char dummy;
    dummy = _spi_read_write(data);
}

/* Function to read a single character from the data register
 */
unsigned char _spi_read() {
    /* Dummy character to write a null byte to SPI
     * Since SPI is always full duplex
     */
    unsigned char dummy = 0x00;
    return _spi_read_write(dummy);
}

/* Function to read a single character from the data register to a memory location
 * @param address - Pointer to the memory location where the 1 byte of character data is stored from the SPI data register
 * IMPORTANT: Please allocate 1 byte of memory at the address of the pointer, otherwise existing data could be overwritten!
 * Please make sure you call address = (char*)(malloc(sizeof(char))); before _spi_read(address);
 */
void _spi_read(unsigned char* address) {
    (*address) = _spi_read();
}

/* Function to read a single character from the data register, and to simultaneously write another single character to it
 * Here data is transferred full duplex
 * @param data - 1 byte of character data to be written to the SPI data register
 * @param SPDR - SPI data register
 */
unsigned char _spi_read_write(unsigned char data) {
	/* The data to be sent is initially written to the SPI data register */
	SPDR = data;

	/* Now we wait for the transmission to complete
	 * @param SPSR - SPI Status Register
     * @param SPIF - SPI Interrupt Flag
     */
	while(!(SPSR & (1<<SPIF)));

	/* The SPI data register now contains data which has been read */
	return SPDR;
}

/* Function to write a string (character array) to SPI at once */
void _spi_write_string(unsigned char *string) {
    uint8_t pos = 0;

    /* A string is a sequence of characters terminated by a null '\0' */
    while(string[pos] != 0x00) {
        _spi_write(string[pos++]);
    }
    /* Ensure proper string termination with null character */
    _spi_write(0x00);
}

#ifndef SPI_MAX_STRING_LENGTH
#define SPI_MAX_STRING_LENGTH 255
#endif // SPI_MAX_STRING_LENGTH
char _spi_buffer[SPI_MAX_STRING_LENGTH];

/* Function to read a string (character array) from SPI at once
 * The maximum length of a transmissible string is 255 by default
 */
unsigned char* _spi_read_string() {
    unsigned char ch;
    uint8_t pos = 0;

    /* A null character '\0' signifies the end of a string */
    while((ch=_spi_read()) != 0x00) {
        _spi_buffer[pos++] = ch;
    }
    /* Ensure proper string termination */
    _spi_buffer[pos] = 0x00;

    return _spi_buffer;
}

/* Function to read a numeric string and return its integer representation through SPI */
int _spi_read_int() {
    return atoi(_spi_read_string());
}

/* Function to write the string representation of an integer through SPI */
void _spi_write_int(int num) {
    _spi_write_string(itoa(num, _spi_buffer, 10));
}

#endif // _SPI_H_
