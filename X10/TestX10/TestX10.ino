#include "WConstants.h" 
#include "X10RF.h"

X10RF moduleX10RF(pinOutRF);
moduleX10RF.x10_sendcmd('C', 1, OFF) ;
