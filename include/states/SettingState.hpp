#pragma once

#include "components/display/OLEDDisplay.hpp"

class SettingState{
public: 
    virtual ~SettingState() = default;
    /**
     * @brief Behandelt eine Drehung des Eingabegeräts.
     *
     * @param delta Die relative Änderung der Drehung.
     */
    virtual void handleRotation(int delta) = 0;

    /**
     * @brief Behandelt einen Knopfdruck.
     */
    virtual void handleButtonPress() = 0;

    /**
     * @brief Aktualisiert die Anzeige basierend auf dem aktuellen Zustand.
     *
     * @param display Das OLEDDisplay-Objekt, das aktualisiert werden soll.
     */
    virtual void updateDisplay(OLEDDisplay* display) = 0;

    /**
     * @brief Setzt den Zustand zurück auf den Standardwert.
     */
    virtual void resetState() = 0;
}