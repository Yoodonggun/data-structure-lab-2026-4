#pragma once
class SportsCar : public car {
public:
    bool bTurbo;
    void setTurbo(bool bTur) { bTurbo = bTur; }
    void speedUp() {
        if (bTurbo) speed += 20;
        else car::speedUp();
    }
};