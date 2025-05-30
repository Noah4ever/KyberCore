# KyberCore ⚡🔦

KyberCore is a high-performance, modular lightsaber firmware designed for ESP32 written in C++. It supports sound, motion effects, Neopixel animation, and robust hardware modularity.

## 🚀 Getting Started

### ✅ Clone the Repository

Simply clone the repository as usual:

```bash
git clone https://github.com/Noah4ever/KyberCore.git
```

### 📦 Install Dependencies with PlatformIO
KyberCore now utilizes PlatformIO's lib_deps feature to manage dependencies. Upon building the project, PlatformIO will automatically download and install all specified libraries.

Ensure you have PlatformIO installed. For installation instructions, visit the PlatformIO Installation Guide.

To build the project:
```bash
cd KyberCore
platformio run
```
This command will compile the project and handle all dependencies as defined in the platformio.ini file.

### 🧩 Adding Custom Libraries

If you're adding your own libraries inside the lib/ directory, please use either:

Flat code (no .git/ folder inside) for static snapshots.
Reference them directly in the platformio.ini using lib_deps.
For example, to include a library from a GitHub repository:

```bash
lib_deps =
  username/custom-library
```

For more details on specifying dependencies, refer to the PlatformIO lib_deps documentation.

## UML-Diagram
![x2KyberCore excalidraw](https://github.com/user-attachments/assets/3097ffd6-ad48-4b42-a3d0-22ba7b7f18c2)

## 🧙 License

KyberCore is licensed under the Apache License 2.0.

Use it wisely, Padawan. Modify, build, and share — but honor the code.
Attribution is the path to the Light Side. ✨⚔️
