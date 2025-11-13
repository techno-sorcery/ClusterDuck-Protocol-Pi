#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);

#else  // __ARM__
#include <malloc.h>
extern char* __brkval;

#endif // __arm__

#ifdef ESP32
    #include "include/DuckEsp.h"
    int freeMemory() {
        return duckesp::freeHeapMemory();
    }

#else
    int freeMemory() {
        char top;

    #ifdef __arm__
        return &top - reinterpret_cast<char*>(sbrk(0));

    #elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
        return &top - __brkval;

    #else  // __arm__
           // return __brkval ? &top - __brkval : &top - __malloc_heap_start;
        return mallinfo2().fordblks;

    #endif // __arm__
    }
#endif //ESP32
