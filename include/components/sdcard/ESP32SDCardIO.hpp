#pragma once

#include "SDCardIO.hpp"
#include <SD.h>
#include <FS.h>
#include <sstream>
#include <vector>
#include <fstream>

class 
ESP32SDCardIO : public SDCardIO {
public:
    ESP32SDCardIO(int csPin = SS) : chipSelectPin(csPin) {}

    bool initializeSD() override {
        if (!SD.begin(chipSelectPin)) {
            Serial.println("SD Card mount failed");
            return false;
        }
        return true;
    }

    bool initializeSD(int csPin) override {
        if (!SD.begin(csPin)) {
            Serial.println("SD Card mount failed");
            return false;
        }
        return true;
    }

    std::string readConfigFile(const std::string& filename) override {
        File configFile = SD.open(("/" + filename).c_str(), FILE_READ);
        if (!configFile || configFile.isDirectory()) {
            Serial.println("Failed to open config file for reading");
            return "";
        }
        std::stringstream ss;
        while (configFile.available()) {
            ss << (char)configFile.read();
        }
        configFile.close();
        return ss.str();
    }

    bool writeConfigFile(const std::string& filename, const std::string& jsonData) override {
        const std::string path = "/" + filename;
        File configFile = SD.open(path.c_str(), FILE_WRITE);
        if (!configFile) {
            Serial.println("Failed to open config file for writing");
            return false;
        }

        if (configFile.print(jsonData.c_str()) == 0) {
            Serial.println("Failed to write to config file");
            configFile.close();
            return false;
        }
        configFile.close();
        return true;
    }

    std::vector<std::string> listAudioFiles(const std::string& path) override {
        std::vector<std::string> files;
        File root = SD.open(path.c_str());
        if (!root || !root.isDirectory()) {
            Serial.println("Failed to open directory");
            return files;
        }
        listDir(SD, path.c_str(), 0, files);
        return files;
    }

    std::vector<uint8_t> readFileBinary(const std::string& filePath) override {
        File file = SD.open(filePath.c_str(), FILE_READ);
        std::vector<uint8_t> data;
        if (file) {
            size_t fileSize = file.size();
            data.resize(fileSize);
            file.read(data.data(), fileSize);
            file.close();
        } else {
            Serial.printf("Failed to open file for reading: %s\n", filePath.c_str());
        }
        return data;
    }

    bool writeFileBinary(const std::string& filePath, const std::vector<uint8_t>& data) override {
        if (!createDirectoryForFile(filePath)) {
            return false;
        }
        File file = SD.open(filePath.c_str(), FILE_WRITE);
        if (file) {
            file.write(data.data(), data.size());
            file.close();
            return true;
        } else {
            Serial.printf("Failed to open file for writing: %s\n", filePath.c_str());
            return false;
        }
    }

    bool createDirectory(const std::string& path) override {
        return SD.mkdir(path.c_str());
    }

    bool exists(const std::string& path) override {
        return SD.exists(path.c_str());
    }

    long long getFreeSpace() override {
        return SD.totalBytes() - SD.usedBytes();
    }

    long long getTotalSpace() override {
        return SD.totalBytes();
    }

private:
    int chipSelectPin;

    void listDir(fs::FS &fs, const char * dirname, uint8_t levels, std::vector<std::string>& files) {
        Serial.printf("Listing directory: %s\n", dirname);

        File root = fs.open(dirname);
        if(!root){
            Serial.println("- failed to open directory");
            return;
        }
        if(!root.isDirectory()){
            Serial.println(" - not a directory");
            return;
        }

        File file = root.openNextFile();
        while(file){
            if(file.isDirectory()){
                if(levels){
                    listDir(fs, file.name(), levels -1, files);
                }
            } else if (endsWith(file.name(), ".mp3") || endsWith(file.name(), ".wav")) {
                const std::string absPath = std::string(dirname) + "/" + file.name();
                files.push_back(absPath);
            }
            file = root.openNextFile();
        }
    }

    bool endsWith(const char *str, const char *suffix) {
        if (!str || !suffix)
            return 0;
        size_t lenstr = strlen(str);
        size_t lensuffix = strlen(suffix);
        if (lensuffix >  lenstr)
            return 0;
        return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
    }

    bool createDirectoryForFile(const std::string& filePath) {
        String path = String(filePath.c_str());
        String dir = "";
        for (int i = 1; i < path.length(); ++i) {
            if (path.charAt(i) == '/') {
                String subDir = path.substring(0, i);
                if (!SD.exists(subDir.c_str())) {
                    Serial.printf("Creating directory: %s\n", subDir.c_str());
                    if (!SD.mkdir(subDir.c_str())) {
                        Serial.printf("Error creating directory: %s\n", subDir.c_str());
                        return false;
                    }
                }
            }
        }
        return true;
    }
};