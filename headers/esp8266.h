/* 
 * File:   esp8266.h
 * Author: jstpa
 *
 * Created on November 13, 2018, 6:38 PM
 */

#ifndef ESP8266_H
#define	ESP8266_H

// AT-Commands
#define ATCWMODE        "AT+CWMODE_CUR=3"   // Set as station / soft AP
#define ATCIPMODE_ON    "AT+CIPMODE=1"      // Set transparent transmission mode
#define ATCIPMODE_OFF   "AT+CIPMODE=0"      // Disable transparent transmission mode
#define ATCIPMUX        "AT+CIPMUX=0"       // Set single connection mode
#define ATCWJAP         "AT+CWJAP_CUR="     // Join access point
#define ATCIPSTART      "AT+CIPSTART="      // Start socket /* NOTE: '0' is for link is invalid bug */
#define ATCIPSEND       "AT+CIPSEND="
#define ATCIPSENDT      "AT+CIPSEND"  
#define ATCIPCLOSE      "AT+CIPClOSE"       // Close socket 
#define ATRESET         "AT+RST"            // Resets the module    

typedef enum {
    TCP, UDP, SSL
}ESP8266_socket_type;

void ESP8266_reset(void);
void ESP8266_query(void);
void ESP8266_init(void);
void ESP8266_connect(char * name, char * pass);
void ESP8266_open_socket(ESP8266_socket_type socket_type, char * ip, int port);
void ESP8266_send_data(char * data);
void ESP8266_start_transparent_xmission(void);
void ESP8266_end_transparent_xmission(void);
void ESP8266_close_socket(void);
char ESP8266_responseOK(void);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* ESP8266_H */

