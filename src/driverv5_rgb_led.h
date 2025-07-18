
#pragma once

#include <Arduino.h>

namespace ynv
{
namespace driverv5
{

class RGBLED
{
   public:
    static RGBLED& getInstance()
    {
        static RGBLED instance;
        return instance;
    }

    void init();

    void red();
    void green();
    void blue();
    void off();

   private:
    RGBLED()                         = default;
    ~RGBLED()                        = default;
    RGBLED(const RGBLED&)            = delete;
    RGBLED& operator=(const RGBLED&) = delete;
};

}  // namespace driverv5
}  // namespace ynv