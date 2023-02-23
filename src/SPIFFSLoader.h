#pragma once

#include <FS.h>
#include <SPIFFS.h>

#include "Debug.h"

class SPIFFSLoader {
public:
    SPIFFSLoader(void);
    virtual ~SPIFFSLoader(void);

    virtual bool begin(void);
    virtual bool load(const char* path);
    virtual bool exists(const char* path);
    virtual bool readFile(const char* path, char* buf, size_t size);
    virtual bool removeFile(const char* path);
};
