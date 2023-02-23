#include "NVSLoader.h"

#include <Arduino_JSON.h>

static const size_t JSON_FILE_BUFFER_SIZE = 1024;

NVSLoader::NVSLoader(const char* nvsNamespace)
    : NAMESPACE{0}, _prefs(), _loader() {
    snprintf(NAMESPACE, sizeof(NAMESPACE), "%s", nvsNamespace);
}

NVSLoader::~NVSLoader(void) {
}

bool NVSLoader::begin(const char* path) {
    if (path == nullptr) {
        SERIAL_PRINTLN("path is null");
        return false;
    }
    if (!this->_loader.begin()) {
        SERIAL_PRINTLN("Failed to mount SPIFFS");
        return false;
    }
    return load(path);
}

bool NVSLoader::get(const char* key, char* buf, size_t size) {
    if (key == nullptr) {
        SERIAL_PRINTLN("key is null");
        return false;
    }
    if (buf == nullptr) {
        SERIAL_PRINTLN("buf is null");
        return false;
    }
    bool result = false;
    if (!this->_prefs.begin(this->NAMESPACE, false)) {
        SERIAL_PRINTF_LN("Failed to initialize NVS: %s", this->NAMESPACE);
        return false;
    }
    if (this->_prefs.isKey(key)) {
        snprintf(buf, size, "%s", this->_prefs.getString(key).c_str());
        result = true;
    }
    this->_prefs.end();
    return result;
}

const char* const NVSLoader::getNamespace(void) const {
    return this->NAMESPACE;
}

bool NVSLoader::load(const char* path) {
    if (path == nullptr) {
        SERIAL_PRINTLN("path is null");
        return false;
    }
    if (this->_loader.exists(path)) {
        SERIAL_PRINTF_LN("Loading from %s", path);
        char jsonBuffer[JSON_FILE_BUFFER_SIZE] = {0};
        if (!this->_loader.readFile(path, jsonBuffer, sizeof(jsonBuffer))) {
            return false;
        }
        if (!this->_loader.removeFile(path)) {
            return false;
        }
        if (!parse(jsonBuffer, sizeof(jsonBuffer))) {
            return false;
        }
    }
    return true;
}

bool NVSLoader::parse(const char* buf, size_t size) {
    JSONVar o = JSON.parse(buf);
    if (JSON.typeof(o) == "undefined") {
        SERIAL_PRINTLN("Failed to parse the JSON content");
        return false;
    }
    SERIAL_PRINTF_LN("Namespace: %s", this->NAMESPACE);

    if (!this->_prefs.begin(this->NAMESPACE, false)) {
        SERIAL_PRINTF_LN("Failed to initialize NVS: %s", this->NAMESPACE);
        return false;
    }
    JSONVar keys = o.keys();
    const char* key = nullptr;
    const char* value = nullptr;
    for (int i = 0; i < keys.length(); ++i) {
        key = (const char*)keys[i];
        value = (const char*)o[keys[i]];
        this->_prefs.putString(key, value);
        SERIAL_PRINTF_LN("Writing NVS: key = %s, value = %s", key, value);
    }
    this->_prefs.end();
    return true;
}