#include <Arduino.h>
namespace WaterPumpCtrl
{
    class waterPumpCtrl
    {
    public:
        String epaperMsg(float sensorValue, int sensorNumber, int pumpNumber);
        bool water(float sensorValue, int sensorNumber, int pumpNumber);
        float calcSoilHumid(int sensorPin, int gndPin);
    };
}