#pragma once

#define CHANNELFROMFLOAT(floatVal, channelVal) if (floatVal <= 0.f){ channelVal = 0; }else{ channelVal = floatVal * 255.; }

