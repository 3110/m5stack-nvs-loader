#include "SPIFFSLoader.h"

static const bool FORMAT_SPIFFS_IF_FAILED = true;

SPIFFSLoader::SPIFFSLoader(void) {
}

SPIFFSLoader::~SPIFFSLoader(void) {
}

bool SPIFFSLoader::begin(void) {
    if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
        SERIAL_PRINTLN("Failed to mount SPIFFS");
        return false;
    }
    return true;
}

bool SPIFFSLoader::load(const char* path) {
    if (path == nullptr) {
        SERIAL_PRINTLN("path is null");
        return false;
    }
    return true;
}

bool SPIFFSLoader::exists(const char* path) {
    if (path == nullptr) {
        SERIAL_PRINTLN("path is null");
        return false;
    }
    return SPIFFS.exists(path);
}

bool SPIFFSLoader::readFile(const char* path, char* buf, size_t size) {
    if (path == nullptr) {
        SERIAL_PRINTLN("path is null");
        return false;
    }
    File f = SPIFFS.open(path, "r");
    if (!f) {
        SERIAL_PRINTF_LN("Can't open file: %s", path);
        return false;
    }
    size_t fileSize = f.size();
    SERIAL_PRINTF_LN("File Size: %d", fileSize);
    if (fileSize > size) {
        SERIAL_PRINTF_LN("Exceed the buffer size %d < %d", size, fileSize);
        return false;
    }
    SERIAL_PRINTLN("Reading: ");
    for (size_t p = 0; f.available() && p < size; ++p) {
        buf[p] = f.read();
        SERIAL_PRINT(buf[p]);
    }
    SERIAL_PRINTLN();
    f.close();
    return true;
}

bool SPIFFSLoader::removeFile(const char* path) {
    if (path == nullptr) {
        SERIAL_PRINTLN("path is null");
        return false;
    }
    if (!SPIFFS.remove(path)) {
        SERIAL_PRINTF_LN("Failed to remove %s", path);
        return false;
    }
    return true;
}
