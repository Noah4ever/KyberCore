# ⚔️ KyberCore

**KyberCore** is a modular C++-based lightsaber control system built for the Raspberry Pi Pico.  
This project controls LEDs, motion, and sound to simulate realistic saber behavior.

---

## 🚀 Getting Started

1. **Install the [Raspberry Pi Pico VSCode Extension](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico).**
2. Open this project in VSCode.
3. Use the **Pico extension sidebar** and click `Compile Project`.
4. **Flash the firmware:**
   - Hold down the `BOOTSEL` button on your Pico.
   - Plug it into your PC while holding it.
   - A USB drive will appear.
   - Copy the generated `build/KyberCore.uf2` file onto the Pico.
   - It will reboot automatically — just like a Jedi awakening.

---

## 📂 Project Structure

```
KyberCore/ 
├── src/ # C++ source files 
│ └── main.cpp # Entry point 
├── include/ # Header files 
│ └── kybercore.h # Shared includes 
├── CMakeLists.txt # Build config 
└── README.md # You're here
```

---

## 🧪 Features (in progress)

- LED blade control (Neopixel or onboard)
- Motion swing detection (MPU9250)
- Sound effects (via DFPlayer Mini)
- Touchpad & potentiometer input
- Modular and expandable C++ structure

---

## 🛡️ License

Apache 2.0  
> *May the source be with you.*

---

## 💡 Dev Tip

Looking to add your own features? The codebase is structured to be modular and easy to extend — just head into `src/` and use the Force responsibly.

---

> ✨ _“This is the core... the KyberCore.”_
