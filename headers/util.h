/* 
 * File:   util.h
 * Author: jstpa
 *
 * Created on November 16, 2018, 8:42 AM
 */

#ifndef UTIL_H
#define	UTIL_H

#define _XTAL_FREQ 16000000
/*
 * Transforms the integer num into a string that is put into buf.
 */
int itoa(int num, char * buf, int radix);
void dtoa(double num, char * buf, int radix);
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* UTIL_H */

