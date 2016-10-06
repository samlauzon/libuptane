

#ifndef __socketcan_wrapper_h
#define __socketcan_wrapper_h

void init_socketcan( void ); 
void send_raw_frame(int id, int dlc, ... ) ;
void send_raw_isotp( ) ;

#endif // __socketcan_wrapper_h

