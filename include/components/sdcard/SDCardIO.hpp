#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class SDCardIO {
public:
    virtual ~SDCardIO() = default;

    /**
     * @brief Initializes the SD card. Must be implemented in the concrete class.
     *
     * @param csPin The chip select pin for the SD card module.
     * @return true on success, false on failure.
     */
    virtual bool initializeSD(int csPin) = 0;

    /**
     * @brief Reads the configuration file in JSON format from the root level of the SD card.
     *
     * @param filename The name of the configuration file (e.g., "config.json").
     * @return A std::string with the content of the file or empty on failure.
     */
    virtual std::string readConfigFile(const std::string& filename) = 0;

    /**
     * @brief Writes data in JSON format to a configuration file at the root level of the SD card.
     *
     * @param filename The name of the configuration file (e.g., "config.json").
     * @param jsonData The JSON data as std::string.
     * @return true on success, false on failure.
     */
    virtual bool writeConfigFile(const std::string& filename, const std::string& jsonData) = 0;

    /**
     * @brief Lists all audio files (MP3 and WAV) in a given directory and its subdirectories.
     *
     * @param path The path to the starting directory (e.g., "/audio").
     * @return A vector of std::string with the full paths to the found files.
     */
    virtual std::vector<std::string> listAudioFiles(const std::string& path) = 0;

    /**
     * @brief Reads the content of a file from the SD card as binary data.
     *
     * @param filePath The full path to the file.
     * @return A vector of bytes (std::vector<uint8_t>) with the file content or empty on failure.
     */
    virtual std::vector<uint8_t> readFileBinary(const std::string& filePath) = 0;

    /**
     * @brief Writes binary data to a file on the SD card. Creates necessary directories if they don't exist.
     *
     * @param filePath The full path to the target file.
     * @param data The binary data to write.
     * @return true on success, false on failure.
     */
    virtual bool writeFileBinary(const std::string& filePath, const std::vector<uint8_t>& data) = 0;

    /**
     * @brief Creates a directory (folder) on the SD card. Creates necessary parent directories if they don't exist.
     *
     * @param path The full path to the directory to create.
     * @return true on success, false on failure.
     */
    virtual bool createDirectory(const std::string& path) = 0;

    /**
     * @brief Checks if a file or directory exists on the SD card.
     *
     * @param path The full path to the file or directory.
     * @return true if exists, false otherwise.
     */
    virtual bool exists(const std::string& path) = 0;

    /**
     * @brief Gets the free space on the SD card in bytes.
     *
     * @return The number of free bytes or -1 on failure.
     */
    virtual long long getFreeSpace() = 0;

    /**
     * @brief Gets the total size of the SD card in bytes.
     *
     * @return The total size in bytes or -1 on failure.
     */
    virtual long long getTotalSpace() = 0;

protected:
    SDCardIO() = default; // Prevents direct instantiation of the abstract class
};