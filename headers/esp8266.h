/* 
 * File:   esp8266.h
 * Author: jstpa
 *
 * Created on November 13, 2018, 6:38 PM
 */

#ifndef ESP8266_H
#define	ESP8266_H

// AT-Commands
#define ATCWJAP "AT+CWJAP=" // Join access point
#define ATCIPSTART "AT+CIPSTART=" // Start socket
#define ATCIPCLOSE "AT+CIPClOSE"  // Close socket 
#define ATCIPSEND "AT+CIPSEND=" // Send data

void ESP8266_init();
void ESP8266_connect(char * name, char * pass);
void ESP8266_open_socket(int socket_type, char * ip, int port);
void ESP8266_send_data(char * data, int len);
void ESP8266_close_socket();

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* ESP8266_H */

