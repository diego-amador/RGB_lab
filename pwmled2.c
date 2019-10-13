/*
 * Copyright (c) 2015-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== pwmled2.c ========
 */
/* For usleep() */
#include <unistd.h>
#include <stddef.h>

#include <ti/drivers/GPIO.h>

/* Driver Header files */
#include <ti/drivers/PWM.h>

/* Example/Board Header files */
#include "Board.h"
int color=1;

    uint16_t   blueDuty = 1000;
    uint16_t   redDuty = 0;
    uint16_t   greenDuty = 0;


    int flag =0;


void gpioButtonFxn1(uint_least8_t index)
{
    /* Clear the GPIO interrupt and toggle an LED */
    if((color==1) && (flag ==0))
    {


        redDuty = 0;
        greenDuty = 1000;
        blueDuty = 0;

        flag=1;
        color =2;
    }

    if((color==2) && (flag ==0))
        {


            redDuty = 1000;
            greenDuty = 0;
            blueDuty = 0;
            flag=1;
            color=3;
        }

    if((color==3) && (flag ==0))
            {


                redDuty = 1000;
                greenDuty = 33;
                blueDuty = 851;
                flag=1;
                color=4;
            }

    if((color==4) && (flag ==0))
              {


                  redDuty = 33;
                  greenDuty = 871;
                  blueDuty = 988;
                  flag=1;
                  color=5;
              }

    if((color==5) && (flag==0))
                 {


                     redDuty = 941;
                     greenDuty = 784;
                     blueDuty = 157;
                     flag=1;
                     color=6;
                 }

    if((color==6) && (flag ==0))
                    {


                        redDuty = 1000;
                        greenDuty = 482;
                        blueDuty = 129;
                        flag=1;
                        color=7;
                    }

    if((color==7) && (flag ==0))
                      {


                          redDuty = 1000;
                          greenDuty = 1000;
                          blueDuty = 1000;
                          flag=1;
                          color=8;
                      }

    if((color==8) && (flag ==0))
                      {


                          redDuty = 0;
                          greenDuty = 0;
                          blueDuty = 1000;
                          flag=1;
                          color=1;
                      }


    usleep(time);
}
/*
 *  ======== mainThread ========
 *  Task periodically increments the PWM duty for the on board LED.
 */
void *mainThread(void *arg0)
{

    GPIO_init();

    GPIO_setConfig(Board_GPIO_BUTTON0, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_RISING);
    GPIO_setCallback(Board_GPIO_BUTTON0, gpioButtonFxn1);
    GPIO_enableInt(Board_GPIO_BUTTON0);
    /* Period and duty in microseconds */
    uint16_t   pwmPeriod = 1000;

    /* Sleep time in microseconds */
    uint32_t   time = 50000;
    PWM_Handle pwm1 = NULL; //pin 01 BLUE
    PWM_Handle pwm2 = NULL; //pin 02 RED
    PWM_Handle pwm3 = NULL; //pin 64 GREEN
    PWM_Params params;

    /* Call driver init functions. */
    PWM_init();

    PWM_Params_init(&params);
    params.dutyUnits = PWM_DUTY_US;
    params.dutyValue = 0;
    params.periodUnits = PWM_PERIOD_US;
    params.periodValue = pwmPeriod;


    pwm1 = PWM_open(Board_PWM0, &params);
    if (pwm1 == NULL) {
        /* Board_PWM0 did not open */
        while (1);
    }

    PWM_start(pwm1);

    pwm2 = PWM_open(Board_PWM1, &params);
    if (pwm2 == NULL) {
        /* Board_PWM1 did not open */
        while (1);
    }

    PWM_start(pwm2);


    pwm3 = PWM_open(Board_PWM2, &params);
            if (pwm3 == NULL) {
                /* Board_PWM2 did not open */
                while (1);
            }

            PWM_start(pwm3);


    while (1) {


        PWM_setDuty(pwm1, blueDuty);

        PWM_setDuty(pwm2, redDuty);

        PWM_setDuty(pwm3, greenDuty);

        flag =0;




    }
}
