/**
 * @file DecagonCTD.h
 * @copyright 2020 Stroud Water Research Center
 * Part of the EnviroDIY ModularSensors library for Arduino
 * @author Sara Geleskie Damiano <sdamiano@stroudcenter.org>
 *
 * @brief Contains the DecagonCTD subclass of the SDI12Sensors class along with
 * the variable subclasses DecagonCTD_Cond, DecagonCTD_Temp, and
 * DecagonCTD_Depth.
 *
 * These are used for the Meter Hydros 21, formerly known as the Decagon Devices
 * CTD-10.
 *
 * This depends on the EnviroDIY SDI-12 library and the SDI12Sensors super
 * class.
 */
/* clang-format off */
/**
 * @defgroup hydros21_group Meter Hydros 21
 * Classes for the Meter Hydros 21 conductivity, temperature, and depth sensor.
 *
 * @ingroup sdi12_group
 *
 * @tableofcontents
 * @m_footernavigation
 *
 * @section hydros21_intro Introduction
 *
 * @note Meter Environmental was formerly known as Decagon Devices and sold the
 * a very similar sensor to the current Hydros 21 as the CTD-10.
 *
 * The Hydros 21 is implemented as a sub-classes of the SDI12Sensors class.
 * It requires a 3.5-12V power supply, which can be turned off between
 * measurements. While contrary to the manual, they will run with power as low
 * as 3.3V.
 *
 * @section hydros21_datasheet Sensor Datasheet
 * Documentation for the SDI-12 Protocol commands and responses for the Hydros
 * 21 can be found at: http://library.metergroup.com/Manuals/13869_CTD_Web.pdf
 *
 * ___
 * @section hydros21_examples Example Code
 * The Meter Hydros21 is used in the @menulink{hydros21} example.
 *
 * @menusnip{hydros21}
 */
/* clang-format on */

// Header Guards
#ifndef SRC_SENSORS_DECAGONCTD_H_
#define SRC_SENSORS_DECAGONCTD_H_

// Included Dependencies
#include "sensors/SDI12Sensors.h"

// Sensor Specific Defines
/** @ingroup hydros21_group */
/**@{*/

/// @brief Sensor::_numReturnedValues; the CTD can report 3 values.
#define CTD_NUM_VARIABLES 3

/**
 * @anchor hydros21_timing_defines
 * @name Sensor Timing
 * Defines for the sensor timing for a Meter Hydros 21
 */
/**@{*/
/// @brief Sensor::_warmUpTime_ms; maximum warm-up time in SDI-12 mode: 500ms
#define CTD_WARM_UP_TIME_MS 500
/// @brief Sensor::_stabilizationTime_ms; the CTD is stable as soon as it warms
/// up (0ms stabilization).
#define CTD_STABILIZATION_TIME_MS 0
/// @brief Sensor::_measurementTime_ms; maximum measurement duration: 500ms.
#define CTD_MEASUREMENT_TIME_MS 500
/**@}*/

/**
 * @anchor hydros21_cond_defines
 * @name Conductivity
 * Defines for the conductivity variable from a Meter Hydros 21
 * - Range is 0 – 120 mS/cm (bulk)
 * - Accuracy is ±0.01mS/cm or ±10% (whichever is greater)
 */
/**@{*/
/**
 * @brief Decimals places in string representation; conductivity should have 1.
 *
 * 0 are reported, adding extra digit to resolution to allow the proper number
 * of significant figures for averaging - resolution is 0.001 mS/cm = 1 µS/cm
 */
#define CTD_COND_RESOLUTION 1
/// @brief Variable number; conductivity is stored in sensorValues[2].
#define CTD_COND_VAR_NUM 2
/// @brief Variable name; "specificConductance"
#define CTD_COND_VAR_NAME "specificConductance"
/// @brief Variable unit name; "microsiemenPerCentimeter" (µS/cm)
#define CTD_COND_UNIT_NAME "microsiemenPerCentimeter"
/// @brief Default variable short code; "CTDcond"
#define CTD_COND_DEFAULT_CODE "CTDcond"
/**@}*/

/**
 * @anchor hydros21_temp_defines
 * @name Temperature
 * Defines for the temperature variable from a Meter Hydros 21
 * - Range is -11°C to +49°C
 * - Accuracy is ±1°C
 */
/**
 * @brief Decimals places in string representation; temperature should have 2.
 *
 * 1 is reported, adding extra digit to resolution to allow the proper number
 * of significant figures for averaging  - resolution is 0.1°C
 */
#define CTD_TEMP_RESOLUTION 2
/// @brief Variable number; temperature is stored in sensorValues[1].
#define CTD_TEMP_VAR_NUM 1
/// @brief Variable name; "temperature"
#define CTD_TEMP_VAR_NAME "temperature"
/// @brief Variable unit name; "degreeCelsius"
#define CTD_TEMP_UNIT_NAME "degreeCelsius"
/// @brief Default variable short code; "CTDtemp"
#define CTD_TEMP_DEFAULT_CODE "CTDtemp"
/**@}*/

/**
 * @anchor hydros21_depth_defines
 * @name Water Depth
 * Defines for the water depth variable from a Meter Hydros 21
 * - Range is 0 to 5 m or 0 to 10 m, depending on model
 * - Accuracy is ±0.05% of full scale
 */
/**
 * @brief Decimals places in string representation; depth should have 1.
 *
 * 0 are reported, adding extra digit to resolution to allow the proper number
 * of significant figures for averaging - resolution is 2 mm
 */
#define CTD_DEPTH_RESOLUTION 1
/// @brief Variable number; depth is stored in sensorValues[0].
#define CTD_DEPTH_VAR_NUM 0
/// @brief Variable name; "waterDepth"
#define CTD_DEPTH_VAR_NAME "waterDepth"
/// @brief Variable unit name; "millimeter"
#define CTD_DEPTH_UNIT_NAME "millimeter"
/// @brief Default variable short code; "CTDdepth"
#define CTD_DEPTH_DEFAULT_CODE "CTDdepth"
/**@}*/


/* clang-format off */
/**
 * @brief The Sensor sub-class for the
 * [Meter Hydros 21 conductivity, temperature, and depth sensor](hydros21_group)
 *
 * @ingroup hydros21_group
 */
/* clang-format on */
class DecagonCTD : public SDI12Sensors {
 public:
    // Constructors with overloads
    /**
     * @brief Construct a new Decagon CTD object.
     * @ingroup hydros21_group
     *
     * The SDI-12 address of the sensor, the Arduino pin controlling power
     * on/off, and the Arduino pin sending and receiving data are required for
     * the sensor constructor.  Optionally, you can include a number of distinct
     * readings to average.  The data pin must be a pin that supports pin-change
     * interrupts.
     *
     * @param SDI12address The SDI-12 address of the Hydros 21.
     * @warning The SDI-12 address **must** be changed from the factory
     * programmed value of "0" before the Hydros 21 can be used with
     * ModularSensors!
     * @param powerPin The pin on the mcu controlling power to the Hydros 21.
     * Use -1 if it is continuously powered.
     * - The Hydros 21 requires a 3.5-12V power supply, which can be turned off
     * between measurements
     * @param dataPin The pin on the mcu connected to the data line of the
     * SDI-12 circuit.
     * @param measurementsToAverage The number of measurements to take and
     * average before giving a "final" result from the sensor; optional with a
     * default value of 1.
     */
    DecagonCTD(char SDI12address, int8_t powerPin, int8_t dataPin,
               uint8_t measurementsToAverage = 1)
        : SDI12Sensors(SDI12address, powerPin, dataPin, measurementsToAverage,
                       "DecagonCTD", CTD_NUM_VARIABLES, CTD_WARM_UP_TIME_MS,
                       CTD_STABILIZATION_TIME_MS, CTD_MEASUREMENT_TIME_MS) {}
    /**
     * @copydoc DecagonCTD::DecagonCTD
     * @ingroup hydros21_group
     */
    DecagonCTD(char* SDI12address, int8_t powerPin, int8_t dataPin,
               uint8_t measurementsToAverage = 1)
        : SDI12Sensors(SDI12address, powerPin, dataPin, measurementsToAverage,
                       "DecagonCTD", CTD_NUM_VARIABLES, CTD_WARM_UP_TIME_MS,
                       CTD_STABILIZATION_TIME_MS, CTD_MEASUREMENT_TIME_MS) {}
    /**
     * @copydoc DecagonCTD::DecagonCTD
     * @ingroup hydros21_group
     */
    DecagonCTD(int SDI12address, int8_t powerPin, int8_t dataPin,
               uint8_t measurementsToAverage = 1)
        : SDI12Sensors(SDI12address, powerPin, dataPin, measurementsToAverage,
                       "DecagonCTD", CTD_NUM_VARIABLES, CTD_WARM_UP_TIME_MS,
                       CTD_STABILIZATION_TIME_MS, CTD_MEASUREMENT_TIME_MS) {}

    /**
     * @brief Destroy the Decagon CTD object
     */
    ~DecagonCTD() {}
};


/* clang-format off */
/**
 * @brief The Variable sub-class used for the
 * [conductivity output](hydros21_cond) from a
 * [Meter Hydros 21 3-in-1 water level sensor.](hydros21_group)
 *
 * @ingroup hydros21_group
 */
/* clang-format on */
class DecagonCTD_Cond : public Variable {
 public:
    /**
     * @brief Construct a new DecagonCTD_Cond object.
     * @ingroup hydros21_group
     *
     * @param parentSense The parent DecagonCTD providing the result values.
     * @param uuid A universally unique identifier (UUID or GUID) for the
     * variable; optional with the default value of an empty string.
     * @param varCode A short code to help identify the variable in files;
     * optional with a default value of "CTDcond".
     */
    explicit DecagonCTD_Cond(DecagonCTD* parentSense, const char* uuid = "",
                             const char* varCode = CTD_COND_DEFAULT_CODE)
        : Variable(parentSense, (const uint8_t)CTD_COND_VAR_NUM,
                   (uint8_t)CTD_COND_RESOLUTION, CTD_COND_VAR_NAME,
                   CTD_COND_UNIT_NAME, varCode, uuid) {}
    /**
     * @brief Construct a new DecagonCTD_Cond object.
     *
     * @note This must be tied with a parent DecagonCTD before it can be used.
     */
    DecagonCTD_Cond()
        : Variable((const uint8_t)CTD_COND_VAR_NUM,
                   (uint8_t)CTD_COND_RESOLUTION, CTD_COND_VAR_NAME,
                   CTD_COND_UNIT_NAME, CTD_COND_DEFAULT_CODE) {}
    /**
     * @brief Destroy the DecagonCTD_Cond object - no action needed.
     */
    ~DecagonCTD_Cond() {}
};


/* clang-format off */
/**
 * @brief The Variable sub-class used for the
 * [temperature Output](hydros21_temp) from a
 * [Meter Hydros 21 3-in-1 water level sensor.](hydros21_group)
 *
 * @ingroup hydros21_group
 */
/* clang-format on */
class DecagonCTD_Temp : public Variable {
 public:
    /**
     * @brief Construct a new DecagonCTD_Temp object.
     * @ingroup hydros21_group
     *
     * @param parentSense The parent DecagonCTD providing the result values.
     * @param uuid A universally unique identifier (UUID or GUID) for the
     * variable; optional with the default value of an empty string.
     * @param varCode A short code to help identify the variable in files;
     * optional with a default value of "CTDtemp".
     */
    explicit DecagonCTD_Temp(DecagonCTD* parentSense, const char* uuid = "",
                             const char* varCode = CTD_TEMP_DEFAULT_CODE)
        : Variable(parentSense, (const uint8_t)CTD_TEMP_VAR_NUM,
                   (uint8_t)CTD_TEMP_RESOLUTION, CTD_TEMP_VAR_NAME,
                   CTD_TEMP_UNIT_NAME, varCode, uuid) {}
    /**
     * @brief Construct a new DecagonCTD_Temp object.
     *
     * @note This must be tied with a parent DecagonCTD before it can be used.
     */
    DecagonCTD_Temp()
        : Variable((const uint8_t)CTD_TEMP_VAR_NUM,
                   (uint8_t)CTD_TEMP_RESOLUTION, CTD_TEMP_VAR_NAME,
                   CTD_TEMP_UNIT_NAME, CTD_TEMP_DEFAULT_CODE) {}
    /**
     * @brief Destroy the DecagonCTD_Temp object - no action needed.
     */
    ~DecagonCTD_Temp() {}
};


/* clang-format off */
/**
 * @brief The Variable sub-class used for the
 * [depth output](hydros21_depth) from a
 * [Meter Hydros 21 3-in-1 water level sensor.](hydros21_group)
 *
 * @ingroup hydros21_group
 */
/* clang-format on */
class DecagonCTD_Depth : public Variable {
 public:
    /**
     * @brief Construct a new DecagonCTD_Depth object.
     * @ingroup hydros21_group
     *
     * @param parentSense The parent DecagonCTD providing the result values.
     * @param uuid A universally unique identifier (UUID or GUID) for the
     * variable; optional with the default value of an empty string.
     * @param varCode A short code to help identify the variable in files;
     * optional with a default value of "CTDdepth".
     */
    explicit DecagonCTD_Depth(DecagonCTD* parentSense, const char* uuid = "",
                              const char* varCode = CTD_DEPTH_DEFAULT_CODE)
        : Variable(parentSense, (const uint8_t)CTD_DEPTH_VAR_NUM,
                   (uint8_t)CTD_DEPTH_RESOLUTION, CTD_DEPTH_VAR_NAME,
                   CTD_DEPTH_UNIT_NAME, varCode, uuid) {}
    /**
     * @brief Construct a new DecagonCTD_Depth object.
     *
     * @note This must be tied with a parent DecagonCTD before it can be used.
     */
    DecagonCTD_Depth()
        : Variable((const uint8_t)CTD_DEPTH_VAR_NUM,
                   (uint8_t)CTD_DEPTH_RESOLUTION, CTD_DEPTH_VAR_NAME,
                   CTD_DEPTH_UNIT_NAME, CTD_DEPTH_DEFAULT_CODE) {}
    /**
     * @brief Destroy the DecagonCTD_Depth object - no action needed.
     */
    ~DecagonCTD_Depth() {}
};
/**@}*/
#endif  // SRC_SENSORS_DECAGONCTD_H_
