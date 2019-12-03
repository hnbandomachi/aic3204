/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  AIC3204 Tone
 *
 */
#include "stdio.h"
#include "usbstk5515.h"
#include "math.h"
extern Int16 AIC3204_rset(Uint16 regnum, Uint16 regval);
#define Rcv 0x08
#define XmitL 0x10
#define XmitR 0x20
#define Fs 48000
#define Fa 200
#define Fc 4000
#define PI 3.141592654
/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  AIC3204 Tone                                                            *
 *      Output a 1 kHz tone through the HEADPHONE jack                      *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 aic3204_tone_headphone()
{
  short ptsig3[480];
  Int16 message[8];
  Int16 binary[16];
  short modulated[480];

  int x, Vpp = 2;
  int nsample = 480;
  Int16 data3;
  Int16 j, i = 0;
  Int16 recevoir[480];

  /* Pre-generated sine wave data, 16-bit signed samples */

  /* Configure AIC3204 */
  AIC3204_rset(0, 0); // Select page 0
  AIC3204_rset(1, 1); // Reset codec
  AIC3204_rset(0, 1); // Select page 1
  AIC3204_rset(1, 8); // Disable crude AVDD generation from DVDD
  AIC3204_rset(2, 1); // Enable Analog Blocks, use LDO power
  AIC3204_rset(0, 0);
  /* PLL and Clocks config and Power Up  */
  AIC3204_rset(27, 0x0d); // BCLK and WCLK are set as o/p; AIC3204(Master)
  AIC3204_rset(28, 0x00); // Data ofset = 0
  AIC3204_rset(4, 3);     // PLL setting: PLLCLK <- MCLK, CODEC_CLKIN <-PLL CLK
  AIC3204_rset(6, 7);     // PLL setting: J=7
  AIC3204_rset(7, 0x06);  // PLL setting: HI_BYTE(D=1680)
  AIC3204_rset(8, 0x90);  // PLL setting: LO_BYTE(D=1680)
  AIC3204_rset(30, 0x88); // For 32 bit clocks per frame in Master mode ONLY
                          // BCLK=DAC_CLK/N =(12288000/8) = 1.536MHz = 32*fs
  AIC3204_rset(5, 0x91);  // PLL setting: Power up PLL, P=1 and R=1
  AIC3204_rset(13, 0);    // Hi_Byte(DOSR) for DOSR = 128 decimal or 0x0080 DAC oversamppling
  AIC3204_rset(14, 0x80); // Lo_Byte(DOSR) for DOSR = 128 decimal or 0x0080
  AIC3204_rset(20, 0x80); // AOSR for AOSR = 128 decimal or 0x0080 for decimation filters 1 to 6
  AIC3204_rset(11, 0x82); // Power up NDAC and set NDAC value to 2
  AIC3204_rset(12, 0x87); // Power up MDAC and set MDAC value to 7
  AIC3204_rset(18, 0x87); // Power up NADC and set NADC value to 7
  AIC3204_rset(19, 0x82); // Power up MADC and set MADC value to 2
  /* DAC ROUTING and Power Up */
  AIC3204_rset(0, 1);       // Select page 1
  AIC3204_rset(0x0c, 8);    // LDAC AFIR routed to HPL
  AIC3204_rset(0x0d, 8);    // RDAC AFIR routed to HPR
  AIC3204_rset(0, 0);       // Select page 0
  AIC3204_rset(64, 2);      // Left vol=right vol
  AIC3204_rset(65, 0);      // Left DAC gain to 0dB VOL; Right tracks Left
  AIC3204_rset(63, 0xd4);   // Power up left,right data paths and set channel
  AIC3204_rset(0, 1);       // Select page 1
  AIC3204_rset(0x10, 0x00); // Unmute HPL , 0dB gain
  AIC3204_rset(0x11, 0x00); // Unmute HPR , 0dB gain
  AIC3204_rset(9, 0x30);    // Power up HPL,HPR
  AIC3204_rset(0, 0);       // Select page 0
  USBSTK5515_wait(100);     // wait
  /* ADC ROUTING and Power Up */
  AIC3204_rset(0, 1);       // Select page 1
  AIC3204_rset(0x34, 0x30); // STEREO 1 Jack
                            // IN2_L to LADC_P through 40 kohm
  AIC3204_rset(0x37, 0x30); // IN2_R to RADC_P through 40 kohmm
  AIC3204_rset(0x36, 3);    // CM_1 (common mode) to LADC_M through 40 kohm
  AIC3204_rset(0x39, 0xc0); // CM_1 (common mode) to RADC_M through 40 kohm
  AIC3204_rset(0x3b, 0);    // MIC_PGA_L unmute
  AIC3204_rset(0x3c, 0);    // MIC_PGA_R unmute
  AIC3204_rset(0, 0);       // Select page 0
  AIC3204_rset(0x51, 0xc0); // Powerup Left and Right ADC
  AIC3204_rset(0x52, 0);    // Unmute Left and Right ADC

  AIC3204_rset(0, 0);
  USBSTK5515_wait(200); // Wait

  /* I2S settings */
  I2S0_SRGR = 0x0;
  I2S0_CR = 0x8010; // 16-bit word, slave, enable I2C
  I2S0_ICMR = 0x3f; // Enable interrupts


  // Lấy 480 giá trị mẫu của xung vuông
  // for (i = 0; i < 1; i++)
  // {
  //   for (j = 0; j < 10; j++)
  //   {
  //     for (x = 0; x < 480; x++)
  //     {
  //       /* Read Digital audio */
  //       while ((Rcv & I2S0_IR) == 0);                    // Wait for interrupt pending flag
  //       data3 = I2S0_W0_MSW_R; // 16 bit left channel received audio data

  //       if (data3 > 0)
  //       {
  //         data3 = 1;
  //       }
  //       else
  //       {
  //         data3 = 0;
  //       }
  //       recevoir[x] = data3;
  //     }
  //   }
  // }

  // In ra 480 giá trị mẫu của xung vuông vừa nhận được ở trên
  // for (x = 0; x < 480; x++)
  // {
  //   printf("%d\n", recevoir[x]);
  // }

  // Đưa 480 giá trị mẫu vào message có kích thước là 8
  i = 0;
  // for (x = 0; x < 480; x++)
  // {
  //   if (abs(recevoir[x + 1] - recevoir[x]) == 1)
  //   {
  //     message[i] = recevoir[x];
  //     i++;
  //   }
  //   if (i > 8)
  //   {
  //     break;
  //   }
  // }

  // Nhập chuỗi 0 - 1 kích thước 16
  printf("\nInput your binary-message\n");
  for (i = 0; i < 16; i++) {
    printf("INPUT: "); scanf("%d", &binary[i]);
  }

  // Xử lí giá trị message
  for (i = 0; i < 8; i++)
  {
    message[i] = binary[2*i]*2 + binary[2*i + 1];
    printf("message = %d\n", message[i]);
  }  

  // OK với message 8 phần tử.
  for (x = 0; x < nsample; x++)
  {
    modulated[x] = 1333 * Vpp * sin(2 * PI * x * Fc / Fs) * message[x / 60];
  }

  for (x = 0; x < nsample; x++)
  {
    ptsig3[x] = modulated[x];
  }

  printf("Play tone\n");
  /* Play Tone */
  for (i = 0; i < 100; i++)
  {
    for (j = 0; j < 1000; j++)
    {
      for (x = 0; x < nsample; x++)
      {
        while ((XmitR & I2S0_IR) == 0);                             // Wait for transmit interrupt to be pending
        I2S0_W0_MSW_W = (modulated[x]); // 16 bit left channel transmit audio data
        I2S0_W1_MSW_W = 0;              // 16 bit right channel transmit audio data
                                        //printf("k is %d \n", I2S0_W0_MSW_W);
      }
    }
  }
  /* Disble I2S */
  I2S0_CR = 0x00;

  return 0;
}