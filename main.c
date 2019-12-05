/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

#include "stdio.h"
#include "usbstk5515.h"

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Testing Function                                                        *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void TEST_execute( Int16 ( *funchandle )( ), char *testname, Int16 testid )
{
    Int16 status;


    /* Call test function */
    status = funchandle( );

    /* Check for test fail */
    if ( status != 0 )
    {
        /* Print error message */
        printf( "     FAIL... error code %d... quitting\n", status );

        /* Software Breakpoint to Code Composer */
        SW_BREAKPOINT;
    }
    else
    {
        /* Print error message */
        printf( "    PASS\n" );
    }
}

extern Int16 aic3204_test( );

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  main( )                                                                 *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void main( void )
{
    /* Initialize BSL */
    USBSTK5515_init( );
    printf("Course: \tAnalog and Digital Modulation\n");
    printf("Instructor: \tProf. Dr. Thuong Le-Tien\n");
    printf("Topic: \t\tModulating 4-ASK\n");
    printf("Group 1: \tLe Quang Huy \t1611260 \t30 \n");
    printf("\t\tLe Trung Luom \t1611952 \t31 \n");
    printf("\t\tHuynh The Hao \t1610875 \t32 \n");
    TEST_execute( aic3204_test, "AIC3204", 1 );
    SW_BREAKPOINT;
}
