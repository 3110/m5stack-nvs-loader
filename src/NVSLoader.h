#pragma once

#include <Preferences.h>

#include "SPIFFSLoader.h"

class NVSLoader {
public:
    NVSLoader(const char* nvsNamespace);
    virtual ~NVSLoader(void);

    virtual bool begin(const char* path);
    virtual bool get(const char* key, char* buf, size_t size);
    virtual const char* const getNamespace(void) const;

protected:
    virtual bool load(const char* path);
    virtual bool parse(const char* buf, size_t size);

private:
    static const size_t NVS_NAMESPACE_LEN = 15;
    char NAMESPACE[NVS_NAMESPACE_LEN + 1];
    Preferences _prefs;
    SPIFFSLoader _loader;
};
