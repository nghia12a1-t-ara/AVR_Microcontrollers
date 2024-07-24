#ifndef  _EEP_H_
#define  _EEP_H_

#include <stdint.h>

void Write_Pass_toEEP(uint8_t send[6]);
void Read_Pass_fromEEP(uint8_t rec[6]);

#endif /* _EEP_H_ */

