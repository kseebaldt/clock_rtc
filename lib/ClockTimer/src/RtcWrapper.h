#ifndef _RTCWRAPPER_H_
#define _RTCWRAPPER_H_

#ifdef ARDUINO
    #include "RTClib.h"

    typedef RTC_DS1307 RtcWrapper;
#else
    #include "FakeRtc.h"

    class RtcWrapper {
        public:
            boolean begin(void);
            static void adjust(const DateTime& dt);
            uint8_t isrunning(void);
            static DateTime now();
            uint8_t readnvram(uint8_t address);
            void writenvram(uint8_t address, uint8_t data);
    };
#endif

#endif /* _RTCWRAPPER_H_ */
