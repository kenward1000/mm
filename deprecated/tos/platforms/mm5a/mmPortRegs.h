/*
 * Copyright 2014-2015, 2016 (c) Eric B. Decker
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 * - Neither the name of the copyright holders nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * @author Eric B. Decker <cire831@gmail.com>
 */

#ifndef _H_MM_PORT_REGS_H
#define _H_MM_PORT_REGS_H

#ifndef PACKED
#define PACKED __attribute__((__packed__))
#endif

norace static volatile struct {
    uint8_t si446x_irqn         : 1;
    uint8_t gyro_drdy           : 1;
    uint8_t p12                 : 1;
    uint8_t sd_access_sense     : 1;
    uint8_t adc_drdy_n          : 1;
    uint8_t p15                 : 1;
    uint8_t p16                 : 1;
    uint8_t dock_irq            : 1;
  } PACKED mmP1in asm("0x0200");

#define SI446X_IRQN_BIT         0x01
#define SD_ACCESS_SENSE_BIT     0x08

norace static volatile struct {
    uint8_t p10                 : 1;
    uint8_t p11                 : 1;
    uint8_t p12                 : 1;
    uint8_t p13                 : 1;
    uint8_t p14                 : 1;
    uint8_t sd_access_ena_n     : 1;
    uint8_t p16                 : 1;
    uint8_t p17                 : 1;
  } PACKED mmP1out asm("0x0202");

norace static volatile struct {
    uint8_t mag_drdy            : 1;
    uint8_t p21                 : 1;
    uint8_t gyro_irq            : 1;
    uint8_t mag_irq             : 1;
    uint8_t accel_int1          : 1;
    uint8_t p25                 : 1;
    uint8_t accel_int2          : 1;
    uint8_t p27                 : 1;
  } PACKED mmP2in asm("0x0201");

norace static volatile struct {
    uint8_t p20                 : 1;
    uint8_t p21                 : 1;
    uint8_t p22                 : 1;
    uint8_t p23                 : 1;
    uint8_t p24                 : 1;
    uint8_t p25                 : 1;
    uint8_t p26                 : 1;
    uint8_t p27                 : 1;
  } PACKED mmP2out asm("0x0203");

norace static volatile struct {
    uint8_t p30                 : 1;
    uint8_t p31                 : 1;
    uint8_t mems_di             : 1;
    uint8_t p33                 : 1;
    uint8_t p34                 : 1;
    uint8_t dock_di             : 1;
    uint8_t p36                 : 1;
    uint8_t p37                 : 1;
  } PACKED mmP3in asm("0x0220");

norace static volatile struct {
    uint8_t dock_clk            : 1;
    uint8_t mems_do             : 1;
    uint8_t p32                 : 1;
    uint8_t mems_clk            : 1;
    uint8_t dock_do             : 1;
    uint8_t p35                 : 1;
    uint8_t sd_clk              : 1;
    uint8_t adc_do              : 1;
  } PACKED mmP3out asm("0x0222");

norace static volatile struct {
    uint8_t p40                 : 1;
    uint8_t p41                 : 1;
    uint8_t p42                 : 1;
    uint8_t p43                 : 1;
    uint8_t p44                 : 1;
    uint8_t p45                 : 1;
    uint8_t p46                 : 1;
    uint8_t p47                 : 1;
  } PACKED mmP4in asm("0x0221");

norace static volatile struct {
    uint8_t p40                 : 1;
    uint8_t accel_csn           : 1;
    uint8_t p42                 : 1;
    uint8_t p43                 : 1;
    uint8_t gyro_csn            : 1;
    uint8_t p45                 : 1;
    uint8_t mag_csn             : 1;
    uint8_t adc_start           : 1;
  } PACKED mmP4out asm("0x0223");

norace static volatile struct {
    uint8_t p50                 : 1;
    uint8_t p51                 : 1;
    uint8_t gps_awake           : 1;
    uint8_t p53                 : 1;
    uint8_t adc_di              : 1;
    uint8_t p55                 : 1;
    uint8_t p56                 : 1;
    uint8_t sd_di               : 1;
  } PACKED mmP5in asm("0x0240");

#define GSD4E_GPS_AWAKE_BIT 0x04

norace static volatile struct {
    uint8_t mux4x_A             : 1;
    uint8_t mux4x_B             : 1;
    uint8_t p52                 : 1;
    uint8_t gps_csn             : 1;
    uint8_t p54                 : 1;
    uint8_t adc_clk             : 1;
    uint8_t sd_do               : 1;
    uint8_t p57                 : 1;
  } PACKED mmP5out asm("0x0242");

norace static volatile struct {
    uint8_t p60                 : 1;
    uint8_t p61                 : 1;
    uint8_t p62                 : 1;
    uint8_t p63                 : 1;
    uint8_t p64                 : 1;
    uint8_t p65                 : 1;
    uint8_t p66                 : 1;
    uint8_t p67                 : 1;
  } PACKED mmP6in asm("0x0241");

norace static volatile struct {
    uint8_t p60                 : 1;
    uint8_t p61                 : 1;
    uint8_t pwr_3v3_ena         : 1;
    uint8_t p63                 : 1;
    uint8_t solar_ena           : 1;
    uint8_t p65                 : 1;
    uint8_t bat_sense_ena       : 1;
    uint8_t p67                 : 1;
  } PACKED mmP6out asm("0x0243");
  
norace static volatile struct {
    uint8_t p70_xin             : 1;
    uint8_t p71_xout            : 1;
    uint8_t p72                 : 1;
    uint8_t p73                 : 1;
    uint8_t p74                 : 1;
    uint8_t p75                 : 1;
    uint8_t p76                 : 1;
    uint8_t p77                 : 1;
  } PACKED mmP7in asm("0x0260");

norace static volatile struct {
    uint8_t p70                 : 1;
    uint8_t p71                 : 1;
    uint8_t p72                 : 1;
    uint8_t sd_pwr_ena          : 1;
    uint8_t p74                 : 1;
    uint8_t mux2x_A             : 1;
    uint8_t p76                 : 1;
    uint8_t p77                 : 1;
  } PACKED mmP7out asm("0x0262");

norace static volatile struct {
    uint8_t p80                 : 1;
    uint8_t p81                 : 1;
    uint8_t p82                 : 1;
    uint8_t p83                 : 1;
    uint8_t p84                 : 1;
    uint8_t p85                 : 1;
    uint8_t p86                 : 1;
    uint8_t si446x_sdn_in       : 1;
  } PACKED mmP8in asm("0x0261");

#define SI446X_SDN_BIT  0x80

norace static volatile struct {
    uint8_t p80                 : 1;
    uint8_t p81                 : 1;
    uint8_t sd_csn              : 1;
    uint8_t p83                 : 1;
    uint8_t p84                 : 1;
    uint8_t p85                 : 1;
    uint8_t p86                 : 1;
    uint8_t si446x_sdn          : 1;
  } PACKED mmP8out asm("0x0263");

norace static volatile struct {
    uint8_t p90                 : 1;
    uint8_t p91                 : 1;
    uint8_t p92                 : 1;
    uint8_t p93                 : 1;
    uint8_t p94                 : 1;
    uint8_t si446x_miso         : 1;
    uint8_t p96                 : 1;
    uint8_t si446x_csn_in       : 1;
  } PACKED mmP9in asm("0x0280");

#define SI446X_CSN_BIT  0x80

norace static volatile struct {
    uint8_t si446x_clk          : 1;
    uint8_t temp_sda            : 1;
    uint8_t temp_scl            : 1;
    uint8_t p93                 : 1;
    uint8_t si446x_mosi         : 1;
    uint8_t p95                 : 1;
    uint8_t p96                 : 1;
    uint8_t si446x_csn          : 1;
  } PACKED mmP9out asm("0x0282");

norace static volatile struct {
    uint8_t p100                : 1;
    uint8_t p101                : 1;
    uint8_t p102                : 1;
    uint8_t p103                : 1;
    uint8_t p104                : 1;
    uint8_t gps_miso            : 1;
    uint8_t p106                : 1;
    uint8_t p107                : 1;
  } PACKED mmP10in asm("0x0281");

norace static volatile struct {
    uint8_t gps_clk             : 1;
    uint8_t temp_pwr            : 1;
    uint8_t p102                : 1;
    uint8_t p103                : 1;
    uint8_t gps_mosi            : 1;
    uint8_t p105                : 1;
    uint8_t adc_csn             : 1;
    uint8_t p107                : 1;
  } PACKED mmP10out asm("0x0283");

norace static volatile struct {
    uint8_t p110                : 1;
    uint8_t p111                : 1;
    uint8_t p112                : 1;
    uint8_t p113                : 1;
    uint8_t p114                : 1;
    uint8_t p115                : 1;
    uint8_t p116                : 1;
    uint8_t p117                : 1;
  } PACKED mmP11in asm("0x02a0");

norace static volatile struct {
    uint8_t gps_on_off          : 1;
    uint8_t p111                : 1;
    uint8_t gps_reset_n         : 1;
    uint8_t p113                : 1;
    uint8_t p114                : 1;
    uint8_t led_1               : 1;    /* red    */
    uint8_t led_2               : 1;    /* green  */
    uint8_t led_3               : 1;    /* yellow */
  } PACKED mmP11out asm("0x02a2");

norace static volatile struct {
    uint8_t pj0                 : 1;
    uint8_t pj1                 : 1;
    uint8_t pj2                 : 1;
    uint8_t si446x_cts          : 1;
    uint8_t pj4                 : 1;
    uint8_t pj5                 : 1;
    uint8_t pj6                 : 1;
    uint8_t pj7                 : 1;
  } PACKED mmPJin asm("0x0320");

#define SI446X_CTS_BIT  0x08

norace static volatile struct {
    uint8_t pj0                 : 1;
    uint8_t si446x_volt_sel     : 1;
    uint8_t pj2                 : 1;
    uint8_t tell                : 1;
    uint8_t pj4                 : 1;
    uint8_t pj5                 : 1;
    uint8_t pj6                 : 1;
    uint8_t pj7                 : 1;
  } PACKED mmPJout asm("0x0322");

/* radio - si446x */

#define SI446X_CTS_P    (PJIN & SI446X_CTS_BIT)
#define SI446X_IRQN_P   (P1IN & SI446X_IRQN_BIT)
#define SI446X_SDN_IN   (P8IN & SI446X_SDN_BIT)
#define SI446X_CSN_IN   (P9IN & SI446X_CSN_BIT)

#define SI446X_CTS              mmPJin.si446x_cts
#define SI446X_IRQN             mmP1in.si446x_irqn
#define SI446X_SDN              mmP8out.si446x_sdn
#define SI446X_CSN              mmP9out.si446x_csn
#define SI446X_VOLT_SEL         mmPJout.si446x_volt_sel

/* mems */
#define GYRO_DRDY               mmP1in.gyro_drdy
#define GYRO_IRQ                mmP2in.gyro_irq
#define MAG_DRDY                mmP2in.mag_drdy
#define MAG_IRQ                 mmP2in.mag_irq
#define ACCEL_INT1              mmP2in.accel_int1
#define ACCEL_INT2              mmP2in.accel_int2
#define ACCEL_CSN               mmP4out.accel_csn
#define GYRO_CSN                mmP4out.gyro_csn
#define MAG_CSN                 mmP4out.mag_csn

/* micro SD */
#define SD_ACCESS_SENSE_N       (P1IN & SD_ACCESS_SENSE_BIT)
#define SD_ACCESS_ENA_N         mmP1out.sd_access_ena_n
#define SD_PWR_ENA              mmP7out.sd_pwr_ena
#define SD_CSN                  mmP8out.sd_csn

/*
 * The mm5 local processor (lp) runs at 1.8V while the uSD runs at 3.3V.
 * All the h/w connections from the lp to the uSD go through a level
 * shifter.  We can prevent the uSD from being powered by inputs by simply
 * turning off the OE on level shifter.  This is done by simply setting
 * SD_ACCESS_ENA_N to a 1.  Also when the uSD is powered off (via usd_pwr_ena
 * being 0), this also kills power to the Vb side which kills any possibility
 * of any inputs powering the uSD.
 *
 * The cpu definitions for the msp430f5438a, circa 2012, ver 1.4,
 * __MSP430_HEADER_VERSION__ 1064, doesn't define P3SEL.  Rather it defines the
 * 16 bit aggragate port (PBSEL).  Between msp430hardware.h and the TI include
 * file this gets sorted out (P3SEL is renamed to be PBSEL_L).
 *
 * Similarily for P5 (-> PC and P8 -> PD).
 * 21 -> PA, 43 -> PB, 65 -> PC, 87 -> PD, 109 -> PE
 *
 * p3sel -> pbsel_l, p5sel -> pcsel_l, p8dir -> pddir_h
 */

#define SD_PINS_INPUT  do { P3SEL &= ~0x40; P5SEL &= ~0xc0; P8DIR &= ~0x04; } while (0)

/*
 * SD_PINS_SPI will connect the 3 spi lines on the SD to the SPI.
 * And switches the sd_csn (8.2) from input to output,  the value should be
 * a 1 which deselects the sd and tri-states.
 *
 * 3.6, CLK, 5.6-7 SDI, SDO set to SPI Module, SD_CSN switched to output
 * (assumed 1, which is CSN, CS deasserted).
 */
#define SD_PINS_SPI   do { P3SEL |= 0x40; P5SEL |= 0xc0; P8DIR |= 0x04; } while (0)


/* adc */
#define ADC_DRDY_N              mmP1in.adc_drdy_n
#define ADC_START               mmP4out.adc_start
#define ADC_CSN                 mmP10out.adc_csn

/* dock */
#define DOCK_IRQ                mmP1in.dock_irq

/* gps -gsd4e/org */
#define GSD4E_GPS_AWAKE         (P5IN & GSD4E_GPS_AWAKE_BIT)
#define GSD4E_GPS_SET_ONOFF     (mmP11out.gps_on_off = 1)
#define GSD4E_GPS_CLR_ONOFF     (mmP11out.gps_on_off = 0)
#define GSD4E_GPS_RESET         (mmP11out.gps_reset_n = 0)
#define GSD4E_GPS_UNRESET       (mmP11out.gps_reset_n = 1)
#define GSD4E_GPS_CSN            mmP5out.gps_csn

/* power */
#define PWR_3V3_ENA             mmP6out.pwr_3v3_ena
#define SOLAR_ENA               mmP6out.solar_ena
#define BAT_SENSE_ENA           mmP6out.bat_sense_ena
#define TEMP_PWR                mmP10out.temp_pwr

#define TELL                    mmPJout.tell
#define TOGGLE_TELL             do { TELL = 1; TELL = 0; } while(0)

#endif
