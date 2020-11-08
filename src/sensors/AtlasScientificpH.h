/**
 * @file AtlasScientificpH.h
 * @copyright 2020 Stroud Water Research Center
 * Part of the EnviroDIY ModularSensors library for Arduino
 * @author Initial developement for Atlas Sensors was done by Adam Gold
 * Files were edited by Sara Damiano <sdamiano@stroudcenter.org>
 *
 * @brief Contains the AtlasScientificRTD subclass of the AtlasParent sensor
 * class along with the variable subclass AtlasScientificpH_pH.
 *
 * These are used for any sensor attached to an Atlas EZO pH circuit.
 *
 * @copydetails AtlasScientificpH
 */
/* clang-format off */
/**
 * @defgroup atlas_ph_group Atlas EZO-pH
 * Classes for the Atlas Scientific EZO-pH circuit and probe.
 *
 * @ingroup atlas_group
 *
 * @tableofcontents
 * @m_footernavigation
 *
 * @section atlas_ph_datasheet Sensor Datasheet
 * Documentation on the probe and measurement circuit are found here:
 * https://www.atlas-scientific.com/ph.html
 *
 * @section atlas_ph_flags Build flags
 * - `-D MS_ATLAS_SOFTWAREWIRE`
 *      - switches from using hardware I2C to software I2C
 * @warning Either all or none of the Atlas sensors can be using software I2C.
 * Using some Altas sensors with software I2C and others with hardware I2C is
 * not supported.
 *
 * @note Be careful not to mix the similar variable and sensor object names!
 *
 * ___
 * @section atlas_ph_examples Example Code
 * The Atlas pH sensor is used in the @menulink{atlas_ph} example.
 *
 * @menusnip{atlas_ph}
 */
/* clang-format on */

// Header Guards
#ifndef SRC_SENSORS_ATLASSCIENTIFICPH_H_
#define SRC_SENSORS_ATLASSCIENTIFICPH_H_

// Included Dependencies
#include "sensors/AtlasParent.h"


// Sensor Specific Defines
/** @ingroup atlas_ph_group */
/**@{*/

/// @brief Default I2C address is 0x63 (99)
#define ATLAS_PH_I2C_ADDR 0x63
/// @brief Sensor::_numReturnedValues; the Atlas EZO pH circuit can report 1
/// value.
#define ATLAS_PH_NUM_VARIABLES 1

/**
 * @anchor atlas_ph_timing_defines
 * @name Sensor Timing
 * Defines for the sensor timing for an Atlas pH sensor
 */
/**@{*/
/**
 * @brief Sensor::_warmUpTime_ms; the Atlas EZO pH circuit warms up in 850ms.
 *
 * 846 in SRGD Tests
 */
#define ATLAS_PH_WARM_UP_TIME_MS 850
/**
 * @brief Sensor::_stabilizationTime_ms; the Atlas EZO pH circuit is stable 0ms
 * after warm-up (stable at completion of warm up).
 */
#define ATLAS_PH_STABILIZATION_TIME_MS 0
/**
 * @brief Sensor::_measurementTime_ms; the Atlas EZO pH circuit takes
 * 1660ms to complete a measurement.
 *
 * @note Manual says measurement takes 900 ms, but in SRGD tests, no
 * result was available until after 1656 ms.
 */
#define ATLAS_PH_MEASUREMENT_TIME_MS 1660
/**@}*/

/**
 * @anchor atlas_ph_ph_defines
 * @name pH
 * Defines for the pH variable from an Atlas pH sensor
 * - Accuracy is ± 0.002
 * - Range is 0.001 − 14.000
 * @m_span{m-dim}(@ref #ATLAS_PH_RESOLUTION = 3)@m_endspan
 * - Reported as dimensionless pH units
 */
/**@{*/
/// @brief Decimals places in string representation; pH should have 3 -
/// resolution is 0.001.
#define ATLAS_PH_RESOLUTION 3
/// @brief Variable number; pH is stored in sensorValues[0].
#define ATLAS_PH_VAR_NUM 0
/// @brief Variable name; "pH"
#define ATLAS_PH_VAR_NAME "pH"
/// @brief Variable unit name; "pH"
#define ATLAS_PH_UNIT_NAME "pH"
/// @brief Default variable short code; "AtlaspH"
#define ATLAS_PH_DEFAULT_CODE "AtlaspH"
/**@}*/


/* clang-format off */
/**
 * @brief The Sensor sub-class for the
 * [Atlas Scientific pH sensor](@ref atlas_ph_group).
 *
 * @note Be careful not to confuse the similar variable and sensor object names!
 *
 * @ingroup atlas_ph_group
 */
/* clang-format on */
class AtlasScientificpH : public AtlasParent {
 public:
#if defined MS_ATLAS_SOFTWAREWIRE
    /**
     * @brief Construct a new Atlas Scientific pH object using a *software* I2C
     * instance.
     * @ingroup atlas_ph_group
     *
     * @param theI2C A [SoftwareWire](https://github.com/Testato/SoftwareWire)
     * instance for I2C communication.
     * @param powerPin The pin on the mcu controlling powering to the Atlas pH
     * circuit.  Use -1 if it is continuously powered.
     * - Requires a 3.3V and 5V power supply
     * @warning **You must isolate the data lines of all Atlas circuits from the
     * main I2C bus if you wish to turn off their power!**  If you do not
     * isolate them from your main I2C bus and you turn off power to the
     * circuits between measurements the I2C lines will be pulled down to ground
     * causing the I2C bus (and thus your logger) to crash.
     * @param i2cAddressHex The I2C address of the Atlas circuit;
     * optional with the Atlas-supplied default address of 0x63.
     * @param measurementsToAverage The number of measurements to take and
     * average before giving a "final" result from the sensor; optional with a
     * default value of 1.
     */
    AtlasScientificpH(SoftwareWire* theI2C, int8_t powerPin,
                      uint8_t i2cAddressHex         = ATLAS_PH_I2C_ADDR,
                      uint8_t measurementsToAverage = 1)
        : AtlasParent(theI2C, powerPin, i2cAddressHex, measurementsToAverage,
                      "AtlasScientificpH", ATLAS_PH_NUM_VARIABLES,
                      ATLAS_PH_WARM_UP_TIME_MS, ATLAS_PH_STABILIZATION_TIME_MS,
                      ATLAS_PH_MEASUREMENT_TIME_MS) {}
    /**
     * @brief Construct a new Atlas Scientific pH object, also creating a
     * [SoftwareWire](https://github.com/Testato/SoftwareWire) I2C instance for
     * communication with that object.
     * @ingroup atlas_ph_group
     *
     * Currently only
     * [Testato's SoftwareWire](https://github.com/Testato/SoftwareWire) is
     * supported.
     *
     * @note Unless there are address conflicts between I2C devices, you should
     * not create a new I2C instance.
     *
     * @param powerPin The pin on the mcu controlling powering to the Atlas pH
     * circuit.  Use -1 if it is continuously powered.
     * - Requires a 3.3V and 5V power supply
     * @warning **You must isolate the data lines of all Atlas circuits from the
     * main I2C bus if you wish to turn off their power!**  If you do not
     * isolate them from your main I2C bus and you turn off power to the
     * circuits between measurements the I2C lines will be pulled down to ground
     * causing the I2C bus (and thus your logger) to crash.
     * @param dataPin The pin on the mcu that will be used for I2C data (SDA).
     * Must be a valid pin number.
     * @param clockPin The pin on the mcu that will be used for the I2C clock
     * (SCL).  Must be a valid pin number.
     * @param i2cAddressHex The I2C address of the Atlas circuit;
     * optional with the Atlas-supplied default address of 0x63.
     * @param measurementsToAverage The number of measurements to take and
     * average before giving a "final" result from the sensor; optional with a
     * default value of 1.
     */
    AtlasScientificpH(int8_t powerPin, int8_t dataPin, int8_t clockPin,
                      uint8_t i2cAddressHex         = ATLAS_PH_I2C_ADDR,
                      uint8_t measurementsToAverage = 1)
        : AtlasParent(powerPin, dataPin, clockPin, i2cAddressHex,
                      measurementsToAverage, "AtlasScientificpH",
                      ATLAS_PH_NUM_VARIABLES, ATLAS_PH_WARM_UP_TIME_MS,
                      ATLAS_PH_STABILIZATION_TIME_MS,
                      ATLAS_PH_MEASUREMENT_TIME_MS) {}
#else
    /**
     * @brief Construct a new Atlas Scientific pH object using a secondary
     * *hardware* I2C instance.
     * @ingroup atlas_ph_group
     *
     * @param theI2C A TwoWire instance for I2C communication.  Due to the
     * limitations of the Arduino core, only a hardware I2C instance can be
     * used.  For an AVR board, there is only one I2C instance possible and this
     * form of the constructor should not be used.  For a SAMD board, this can
     * be used if a secondary I2C port is created on one of the extra SERCOMs.
     * @param powerPin The pin on the mcu controlling powering to the Atlas pH
     * circuit.  Use -1 if it is continuously powered.
     * - Requires a 3.3V and 5V power supply
     * @warning **You must isolate the data lines of all Atlas circuits from the
     * main I2C bus if you wish to turn off their power!**  If you do not
     * isolate them from your main I2C bus and you turn off power to the
     * circuits between measurements the I2C lines will be pulled down to ground
     * causing the I2C bus (and thus your logger) to crash.
     * @param i2cAddressHex The I2C address of the Atlas circuit;
     * optional with the Atlas-supplied default address of 0x63.
     * @param measurementsToAverage The number of measurements to take and
     * average before giving a "final" result from the sensor; optional with a
     * default value of 1.
     */
    AtlasScientificpH(TwoWire* theI2C, int8_t powerPin,
                      uint8_t i2cAddressHex         = ATLAS_PH_I2C_ADDR,
                      uint8_t measurementsToAverage = 1)
        : AtlasParent(theI2C, powerPin, i2cAddressHex, measurementsToAverage,
                      "AtlasScientificpH", ATLAS_PH_NUM_VARIABLES,
                      ATLAS_PH_WARM_UP_TIME_MS, ATLAS_PH_STABILIZATION_TIME_MS,
                      ATLAS_PH_MEASUREMENT_TIME_MS) {}
    /**
     * @brief Construct a new Atlas Scientific pH object using the primary
     * hardware I2C instance.
     * @ingroup atlas_ph_group
     *
     * @param powerPin The pin on the mcu controlling powering to the Atlas pH
     * circuit.  Use -1 if it is continuously powered.
     * - Requires a 3.3V and 5V power supply
     * @warning **You must isolate the data lines of all Atlas circuits from the
     * main I2C bus if you wish to turn off their power!**  If you do not
     * isolate them from your main I2C bus and you turn off power to the
     * circuits between measurements the I2C lines will be pulled down to ground
     * causing the I2C bus (and thus your logger) to crash.
     * @param i2cAddressHex The I2C address of the Atlas circuit;
     * optional with the Atlas-supplied default address of 0x63.
     * @param measurementsToAverage The number of measurements to take and
     * average before giving a "final" result from the sensor; optional with a
     * default value of 1.
     */
    explicit AtlasScientificpH(int8_t  powerPin,
                               uint8_t i2cAddressHex = ATLAS_PH_I2C_ADDR,
                               uint8_t measurementsToAverage = 1)
        : AtlasParent(powerPin, i2cAddressHex, measurementsToAverage,
                      "AtlasScientificpH", ATLAS_PH_NUM_VARIABLES,
                      ATLAS_PH_WARM_UP_TIME_MS, ATLAS_PH_STABILIZATION_TIME_MS,
                      ATLAS_PH_MEASUREMENT_TIME_MS) {}
#endif
    /**
     * @brief Destroy the Atlas Scientific pH object
     */
    ~AtlasScientificpH() {}
};


/* clang-format off */
/**
 * @brief The Variable sub-class used for the
 * [pH output](@ref atlas_ph_ph) from an
 * [Atlas Scientific EZO pH circuit](@ref atlas_ph_group).
 *
 * @note Be careful not to mix the similar variable and sensor object names!
 *
 * @ingroup atlas_ph_group
 */
/* clang-format on */
class AtlasScientificpH_pH : public Variable {
 public:
    /**
     * @brief Construct a new AtlasScientificpH_pH object.
     * @ingroup atlas_group
     *
     * @param parentSense The parent AtlasScientificpH providing the result
     * values.
     * @param uuid A universally unique identifier (UUID or GUID) for the
     * variable; optional with the default value of an empty string.
     * @param varCode A short code to help identify the variable in files;
     * optional with a default value of "AtlaspH".
     */
    explicit AtlasScientificpH_pH(AtlasScientificpH* parentSense,
                                  const char*        uuid = "",
                                  const char* varCode = ATLAS_PH_DEFAULT_CODE)
        : Variable(parentSense, (const uint8_t)ATLAS_PH_VAR_NUM,
                   (uint8_t)ATLAS_PH_RESOLUTION, ATLAS_PH_VAR_NAME,
                   ATLAS_PH_UNIT_NAME, varCode, uuid) {}
    /**
     * @brief Construct a new AtlasScientificpH_pH object.
     *
     * @note This must be tied with a parent AtlasScientificpH before it can be
     * used.
     */
    AtlasScientificpH_pH()
        : Variable((const uint8_t)ATLAS_PH_VAR_NUM,
                   (uint8_t)ATLAS_PH_RESOLUTION, ATLAS_PH_VAR_NAME,
                   ATLAS_PH_UNIT_NAME, ATLAS_PH_DEFAULT_CODE) {}
    /**
     * @brief Destroy the AtlasScientificpH_pH object - no action needed.
     */
    ~AtlasScientificpH_pH() {}
};
/**@}*/
#endif  // SRC_SENSORS_ATLASSCIENTIFICPH_H_
