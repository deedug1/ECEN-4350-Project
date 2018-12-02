/* 
 * File:   esp8266.h
 * Author: jstpa
 *
 * Created on November 13, 2018, 6:38 PM
 */

#ifndef ESP8266_H
#define	ESP8266_H


typedef enum {
    TCP, UDP, SSL
}ESP8266_socket_type;

void ESP8266_reset(void);
void ESP8266_query(void);
void ESP8266_init(void);
void ESP8266_connect(char * name, char * pass);
void ESP8266_open_socket(ESP8266_socket_type socket_type, char * ip, int port);
void ESP8266_send_data(char * data);
void ESP8266_close_socket(void);
char ESP8266_responseOK(void);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* ESP8266_H */

