#pragma once
#ifndef CableTesters_h
#define CableTesters_h

#include <Arduino.h>

class TestCable
{
  public:
    /**
    * @brief Initialize the library
    *    
    * @param Display_Enable Enable or disable LED display
    *  
    * @param PinErrorLED Error LED pin number
    *  
    * @param PinPassLED Pass LED pin number
    * 
    * @example begin(true, 20, 21);
    *  
    * @return void
    */
    void begin(bool Display_Enable, uint8_t PinErrorLED = 20, uint8_t PinPassLED = 21);
    /**
    * @brief Set pins to input pull up
    *
    * @param PinsToSet Array of pins to set
    *     
    * @param size Size of the array 
    * 
    * @example SetPinsPullUP(AllPins, sizeof(AllPins));
    * 
    * @return void
    */
    void SetPinsPullUP(uint8_t* PinsToSet, size_t size);
    /**
    * @brief Set pins to input pull down
    *
    * @param PinsToSet Array of pins to set
    *     
    * @param size Size of the array 
    * 
    * @example SetPinsPullDown(AllPins, sizeof(AllPins));
    * 
    * @return void
    */
    void SetPinsPullDown(uint8_t* PinsToSet, size_t size);
    /**
    * @brief Set pins to output
    *
    * @param PinsToSet Array of pins to set
    *     
    * @param size Size of the array 
    * 
    * @example SetPinsOutput(AllPins, sizeof(AllPins));
    * 
    * @return void
    */
    void SetPinsOutput(uint8_t* PinsToSet, size_t size);
    /**
    * @brief Set pins to LOW
    * 
    * @param PinsToSet Array of pins to set
    * 
    * @param size Size of the array
    * 
    * @return void
    */
    void SetPinsLOW(uint8_t* PinsToSet, size_t size);
    /**
    * @brief Set pins to HIGH
    * 
    * @param PinsToSet Array of pins to set
    * 
    * @param size Size of the array
    * 
    * @return void
    */
    void SetPinsHIGH(uint8_t* PinsToSet, size_t size);
    /**
    * @brief Blink LED fast (70ms). Non-Inverted.
    *
    * @param pinNo LED pin number
    *     
    * @param times Count of ON/OFF cycles
    * 
    * @return void
    */
    void BlinkLED_fast(uint8_t pinNo, int times);
    /**
    * @brief Blink LED slow (300ms). Non-Inverted.
    *
    * @param pinNo LED pin number
    *     
    * @param times Count of ON/OFF cycles
    * 
    * @return void
    */
    void BlinkLED_slow(uint8_t pinNo, int times);
    /**
    * @brief Blink LED fast (70ms). Inverted.
    *
    * @param pinNo LED pin number
    *     
    * @param times Count of ON/OFF cycles
    * 
    * @return void
    */
    void BlinkLED_fast_inv(uint8_t pinNo, int times);
    /**
    * @brief Blink LED slow (300ms). Inverted.
    *
    * @param pinNo LED pin number
    *     
    * @param times Count of ON/OFF cycles
    * 
    * @return void
    */
    void BlinkLED_slow_inv(uint8_t pinNo, int times);
    /**
    * @brief Set LEDSs for error state. Ends with while(1). Non-Inverted.
    *
    * @param PinErrorLED Error LED pin number
    *     
    * @param PinPassLED Pass LED pin number
    * 
    * @return while(1)
    */
    void SetErrorLEDS(uint8_t PinErrorLED, uint8_t PinPassLED);
    /**
    * @brief Set LEDSs for pass state. Pass LED blinks 5 times for 500ms.  Non-Inverted.
    *
    * @param PinErrorLED Error LED pin number
    *     
    * @param PinPassLED Pass LED pin number
    * 
    * @return void
    */
    void SetPassLEDS(uint8_t PinErrorLED, uint8_t PinPassLED);
    /**
    * @brief Confirm shorts from array
    *
    * @param pins Array of pins to confirm short
    *     
    * @param size Size of the array 
    * 
    * @example ShortsConfirm(Shorts_YellowDB,sizeof(Shorts_YellowDB));
    * 
    * @return uint8_t, error=1, pass=0
    */
    uint8_t ShortsConfirm(uint8_t* pins, size_t size);
    /**
    * @brief Confirm NC from array
    *
    * @param pins Array of pins to confirm NC
    *     
    * @param size Size of the array 
    * 
    * @example NCConfirm(Shorts_YellowDB,sizeof(Shorts_YellowDB));
    * 
    * @return uint8_t, error=1, pass=0
    */
    uint8_t NCConfirm(uint8_t* pins, size_t size);
    /**
    * @brief Diode test function
    * 
    * @param Anode Array of Anode pins
    *
    * @param size_A Size of the Anode array
    *
    * @param Cathode Array of Cathode pins
    *
    * @param size_C Size of the Cathode array
    *
    * @return uint8_t, error=1, pass=0
    */
    uint8_t DiodeTest(uint8_t* Anode, size_t size_A, uint8_t* Cathode, size_t size_C);
    /**
     * @brief Cable detect function
     *  
     * @param SetDetection Pin to set for cable detection
     * 
     * @param DetectionPin Pin to read for detection
     * 
     * @return returns to test execurtion after cable has been detected
     */
    uint8_t CableDetect(uint8_t SetDetection, uint8_t DetectionPin); 
  private:
};
#endif