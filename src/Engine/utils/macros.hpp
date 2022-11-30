#pragma once

#define CHANNELFROMFLOAT(floatVal, channelVal) if (floatVal <= 0.4f){ channelVal = 0; }else{ channelVal = (floatVal * 256.)-1; }

