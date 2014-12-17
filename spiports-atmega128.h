/*
 * SPI Port Definitions for device - Atmega128
 * =========================================
 * Created by Saptarshi Hazra, Shashwata Gupta and Shoumik Ghosal
 *
 * Pin mappings
 * ============
 * PORTB    - Port for SPI
 * DDRB     - Data Direction Register for SPI
 * PB0      - Slave Select (SS)
 * PB2      - Master Out, Slave In (MOSI)
 * PB3      - Master In, Slave Out (MISO)
 * PB1      - Serial Clock (SCK)
 *
 */

#ifndef _SPIPORTS_H_
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

#define SS PB0
#define MOSI PB2
#define MISO PB3
#define SCK PB1

#endif // _SPIPORTS_H_
