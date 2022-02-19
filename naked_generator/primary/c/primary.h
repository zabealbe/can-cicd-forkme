#ifdef __cplusplus
extern "C" {
#endif

#ifndef PRIMARY_H
#define PRIMARY_H

#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <stdio.h>

/*
*   NAKED SHARED 
*   Common functions, defines and checks between all the network.h files
*/
#ifndef __NAKED_SHARED
#define __NAKED_SHARED
    /*
    *   STDC Version check
    *   check if STDC version is greater or equal than the minimum version required
    */
    #define NAKED_STDC_MIN_VERSION 201112L
    #if __STDC_VERSION__ < NAKED_STDC_MIN_VERSION
        #error "** STDC VERSION NOT SUPPORTED **"
    #endif
    
    /*
    *   Endianness check
    *   static check for supported endianness
    */
    #ifndef __NAKED_ENDIAN_ORDER
        #define __NAKED_ENDIAN_ORDER 1094861636L // "ABCD"
    #endif
    #if !defined(__NAKED_LITTLE_ENDIAN) && !defined(__NAKED_BIG_ENDIAN) && !defined(__NAKED_PDP_ENDIAN)
        #if __NAKED_ENDIAN_ORDER==0x41424344UL 
            #define __NAKED_LITTLE_ENDIAN
        #elif __NAKED_ENDIAN_ORDER==0x44434241UL
            #define __NAKED_BIG_ENDIAN
        #elif __NAKED_ENDIAN_ORDER==0x42414443UL
            #define __NAKED_PDP_ENDIAN
        #else
            #error "** HARDWARE ENDIANNESS NOT SUPPORTED **"
        #endif
    #endif
    
    #ifndef __NAKED_LITTLE_ENDIAN
        #error "** HARDWARE ENDIANNESS NOT SUPPORTED **"
    #endif
    
    /*
    *   Floating point types size check
    *   the only supported sizes for now are 32 bits for float and 64 for double
    */
    static_assert(sizeof(float) == 4,"** THIS ARCHITECTURE DOESN'T MATCH THE EXPECTED SIZE FOR 'float' OF 4 BYTES **");
    static_assert(sizeof(double) == 8, "** THIS ARCHITECTURE DOESN'T MATCH THE EXPECTED SIZE FOR 'double' OF 8 BYTES **");

    /*
    *   Packed macro
    *   macro for packed structs on multiple compilers
    */
    #if defined(__MINGW32__)
        #define __is_packed __attribute__((__gcc_struct__, __packed__)) // , __aligned__(1)))
    #else
        #define __is_packed __attribute__((__packed__)) // , __aligned__(1)))
    #endif
    
    /*
    *   Bitset setter/getter
    *   macros for reading/writing bitsets
    */
    #define setBit(bitset, index, value) \
    do { \
        (bitset)[(index)/8] &= ~( 1 << (index) % 8); \
        (bitset)[(index)/8] |=  ((value) << (index) % 8); \
    } while(0);
    #define flipBit(bitset, index) ((bitset)[(index)/8] ^= (1 << (index) % 8) )
    #define getBit(bitset, index)  ((bitset)[(index)/8] &  (1 << (index) % 8) )
#endif


typedef uint8_t primary_pcu_flags[1]; // bitset
#define primary_pcu_flags_default { 0 } // bitset filled with zeros
#define primary_pcu_flags_IMPLAUSIBILITY 0
#define primary_pcu_flags_ADC_ERROR 1
#define primary_pcu_flags_UART_ERROR 2
#define primary_pcu_flags_CALIBRATION_INCOMPLETE 3
#define primary_pcu_flags_CAN_ERROR 4

typedef uint8_t primary_Hv_Errors[2]; // bitset
#define primary_Hv_Errors_default { 0, 0 } // bitset filled with zeros
#define primary_Hv_Errors_LTC_PEC_ERROR 0
#define primary_Hv_Errors_CELL_UNDER_VOLTAGE 1
#define primary_Hv_Errors_CELL_OVER_VOLTAGE 2
#define primary_Hv_Errors_CELL_OVER_TEMPERATURE 3
#define primary_Hv_Errors_OVER_CURRENT 4
#define primary_Hv_Errors_ADC_INIT 5
#define primary_Hv_Errors_ADC_TIMEOUT 6
#define primary_Hv_Errors_INT_VOLTAGE_MISMATCH 7
#define primary_Hv_Errors_FEEDBACK_HARD 8
#define primary_Hv_Errors_FEEDBACK_SOFT 9

typedef enum __is_packed {
    primary_Sync_State_MAX_SET = 0,
    primary_Sync_State_MIN_SET = 1,
} primary_Sync_State;

typedef enum __is_packed {
    primary_Tlm_Status_ON = 0,
    primary_Tlm_Status_OFF = 1,
} primary_Tlm_Status;

typedef enum __is_packed {
    primary_Race_Type_ACCELERATION = 0,
    primary_Race_Type_SKIDPAD = 1,
    primary_Race_Type_AUTOCROSS = 2,
    primary_Race_Type_ENDURANCE = 3,
} primary_Race_Type;

typedef enum __is_packed {
    primary_Car_Status_IDLE = 0,
    primary_Car_Status_SETUP = 1,
    primary_Car_Status_RUN = 2,
} primary_Car_Status;

typedef enum __is_packed {
    primary_Inverter_Status_OFF = 0,
    primary_Inverter_Status_IDLE = 1,
    primary_Inverter_Status_ON = 2,
} primary_Inverter_Status;

typedef enum __is_packed {
    primary_Ts_Status_OFF = 0,
    primary_Ts_Status_PRECHARGE = 1,
    primary_Ts_Status_ON = 2,
    primary_Ts_Status_FATAL = 3,
} primary_Ts_Status;

typedef enum __is_packed {
    primary_Ts_Status_Set_OFF = 0,
    primary_Ts_Status_Set_ON = 1,
} primary_Ts_Status_Set;

typedef enum __is_packed {
    primary_Traction_Control_OFF = 0,
    primary_Traction_Control_SLIP_CONTROL = 1,
    primary_Traction_Control_TORQUE_VECTORING = 2,
    primary_Traction_Control_COMPLETE = 3,
} primary_Traction_Control;

typedef enum __is_packed {
    primary_Map_R = 0,
    primary_Map_D20 = 1,
    primary_Map_D40 = 2,
    primary_Map_D60 = 3,
    primary_Map_D80 = 4,
    primary_Map_D100 = 5,
} primary_Map;

typedef enum __is_packed {
    primary_Car_Status_Set_IDLE = 0,
    primary_Car_Status_Set_RUN = 1,
} primary_Car_Status_Set;

typedef enum __is_packed {
    primary_Status_CHG_OFF = 0,
    primary_Status_CHG_TC = 1,
    primary_Status_CHG_CC = 2,
    primary_Status_CHG_CV = 3,
} primary_Status;

/* primary_SET_ACCELERATOR_RANGE */
typedef struct __is_packed {
    primary_Sync_State sync_state;
} primary_SET_ACCELERATOR_RANGE;
static_assert(sizeof(primary_SET_ACCELERATOR_RANGE) == 1, "struct size mismatch");
    
size_t serialize_primary_SET_ACCELERATOR_RANGE(uint8_t* buffer, primary_Sync_State sync_state);
size_t deserialize_primary_SET_ACCELERATOR_RANGE(uint8_t* buffer, primary_SET_ACCELERATOR_RANGE* primary_set_accelerator_range);

/* primary_PEDALS_ADC_RANGES */
typedef struct __is_packed {
    uint16_t accel1_raw_adc_min;
    uint16_t accel1_raw_adc_max;
    uint16_t accel2_raw_adc_min;
    uint16_t accel2_raw_adc_max;
} primary_PEDALS_ADC_RANGES;
static_assert(sizeof(primary_PEDALS_ADC_RANGES) == 8, "struct size mismatch");
    
size_t serialize_primary_PEDALS_ADC_RANGES(uint8_t* buffer, uint16_t accel1_raw_adc_min, uint16_t accel1_raw_adc_max, uint16_t accel2_raw_adc_min, uint16_t accel2_raw_adc_max);
size_t deserialize_primary_PEDALS_ADC_RANGES(uint8_t* buffer, primary_PEDALS_ADC_RANGES* primary_pedals_adc_ranges);

/* primary_ACCELERATOR_PEDAL_VAL */
typedef struct __is_packed {
    uint8_t level;
} primary_ACCELERATOR_PEDAL_VAL;
static_assert(sizeof(primary_ACCELERATOR_PEDAL_VAL) == 1, "struct size mismatch");
    
size_t serialize_primary_ACCELERATOR_PEDAL_VAL(uint8_t* buffer, uint8_t level);
size_t deserialize_primary_ACCELERATOR_PEDAL_VAL(uint8_t* buffer, primary_ACCELERATOR_PEDAL_VAL* primary_accelerator_pedal_val);

/* primary_BRAKE_PEDAL_VAL */
typedef struct __is_packed {
    uint8_t level;
} primary_BRAKE_PEDAL_VAL;
static_assert(sizeof(primary_BRAKE_PEDAL_VAL) == 1, "struct size mismatch");
    
size_t serialize_primary_BRAKE_PEDAL_VAL(uint8_t* buffer, uint8_t level);
size_t deserialize_primary_BRAKE_PEDAL_VAL(uint8_t* buffer, primary_BRAKE_PEDAL_VAL* primary_brake_pedal_val);

/* primary_PCU_STATUS */
typedef struct __is_packed {
    primary_pcu_flags warnings;
    primary_pcu_flags errors;
} primary_PCU_STATUS;
static_assert(sizeof(primary_PCU_STATUS) == 2, "struct size mismatch");
    
size_t serialize_primary_PCU_STATUS(uint8_t* buffer, primary_pcu_flags warnings, primary_pcu_flags errors);
size_t deserialize_primary_PCU_STATUS(uint8_t* buffer, primary_PCU_STATUS* primary_pcu_status);

/* primary_TIMESTAMP */
typedef struct __is_packed {
    uint32_t timestamp;
} primary_TIMESTAMP;
static_assert(sizeof(primary_TIMESTAMP) == 4, "struct size mismatch");
    
size_t serialize_primary_TIMESTAMP(uint8_t* buffer, uint32_t timestamp);
size_t deserialize_primary_TIMESTAMP(uint8_t* buffer, primary_TIMESTAMP* primary_timestamp);

/* primary_TLM_STATUS */
typedef struct __is_packed {
    primary_Tlm_Status tlm_status;
    primary_Race_Type race_type;
    uint8_t driver;
    uint8_t circuit;
} primary_TLM_STATUS;
static_assert(sizeof(primary_TLM_STATUS) == 4, "struct size mismatch");
    
size_t serialize_primary_TLM_STATUS(uint8_t* buffer, primary_Tlm_Status tlm_status, primary_Race_Type race_type, uint8_t driver, uint8_t circuit);
size_t deserialize_primary_TLM_STATUS(uint8_t* buffer, primary_TLM_STATUS* primary_tlm_status);

/* primary_CAR_STATUS */
typedef struct __is_packed {
    primary_Car_Status car_status;
    primary_Inverter_Status inverter_l;
    primary_Inverter_Status inverter_r;
} primary_CAR_STATUS;
static_assert(sizeof(primary_CAR_STATUS) == 3, "struct size mismatch");
    
size_t serialize_primary_CAR_STATUS(uint8_t* buffer, primary_Car_Status car_status, primary_Inverter_Status inverter_l, primary_Inverter_Status inverter_r);
size_t deserialize_primary_CAR_STATUS(uint8_t* buffer, primary_CAR_STATUS* primary_car_status);

/* primary_SET_TLM_STATUS */
typedef struct __is_packed {
    primary_Tlm_Status tlm_status;
    primary_Race_Type race_type;
    uint8_t driver;
    uint8_t circuit;
} primary_SET_TLM_STATUS;
static_assert(sizeof(primary_SET_TLM_STATUS) == 4, "struct size mismatch");
    
size_t serialize_primary_SET_TLM_STATUS(uint8_t* buffer, primary_Tlm_Status tlm_status, primary_Race_Type race_type, uint8_t driver, uint8_t circuit);
size_t deserialize_primary_SET_TLM_STATUS(uint8_t* buffer, primary_SET_TLM_STATUS* primary_set_tlm_status);

/* primary_GPS_COORDS */
typedef struct __is_packed {
    float latitude;
    float longitude;
} primary_GPS_COORDS;
static_assert(sizeof(primary_GPS_COORDS) == 8, "struct size mismatch");
    
size_t serialize_primary_GPS_COORDS(uint8_t* buffer, float latitude, float longitude);
size_t deserialize_primary_GPS_COORDS(uint8_t* buffer, primary_GPS_COORDS* primary_gps_coords);

/* primary_GPS_SPEED */
typedef struct __is_packed {
    uint16_t speed;
} primary_GPS_SPEED;
static_assert(sizeof(primary_GPS_SPEED) == 2, "struct size mismatch");
    
size_t serialize_primary_GPS_SPEED(uint8_t* buffer, uint16_t speed);
size_t deserialize_primary_GPS_SPEED(uint8_t* buffer, primary_GPS_SPEED* primary_gps_speed);

/* primary_HV_VOLTAGE */
typedef struct __is_packed {
    uint16_t pack_voltage;
    uint16_t bus_voltage;
    uint16_t max_cell_voltage;
    uint16_t min_cell_voltage;
} primary_HV_VOLTAGE;
static_assert(sizeof(primary_HV_VOLTAGE) == 8, "struct size mismatch");
    
size_t serialize_primary_HV_VOLTAGE(uint8_t* buffer, uint16_t pack_voltage, uint16_t bus_voltage, uint16_t max_cell_voltage, uint16_t min_cell_voltage);
size_t deserialize_primary_HV_VOLTAGE(uint8_t* buffer, primary_HV_VOLTAGE* primary_hv_voltage);

/* primary_HV_CURRENT */
typedef struct __is_packed {
    uint16_t current;
    int16_t power;
} primary_HV_CURRENT;
static_assert(sizeof(primary_HV_CURRENT) == 4, "struct size mismatch");
    
size_t serialize_primary_HV_CURRENT(uint8_t* buffer, uint16_t current, int16_t power);
size_t deserialize_primary_HV_CURRENT(uint8_t* buffer, primary_HV_CURRENT* primary_hv_current);

/* primary_HV_TEMP */
typedef struct __is_packed {
    uint16_t average_temp;
    uint16_t max_temp;
    uint16_t min_temp;
} primary_HV_TEMP;
static_assert(sizeof(primary_HV_TEMP) == 6, "struct size mismatch");
    
size_t serialize_primary_HV_TEMP(uint8_t* buffer, uint16_t average_temp, uint16_t max_temp, uint16_t min_temp);
size_t deserialize_primary_HV_TEMP(uint8_t* buffer, primary_HV_TEMP* primary_hv_temp);

/* primary_HV_ERRORS */
typedef struct __is_packed {
    primary_Hv_Errors warnings;
    primary_Hv_Errors errors;
} primary_HV_ERRORS;
static_assert(sizeof(primary_HV_ERRORS) == 4, "struct size mismatch");
    
size_t serialize_primary_HV_ERRORS(uint8_t* buffer, primary_Hv_Errors warnings, primary_Hv_Errors errors);
size_t deserialize_primary_HV_ERRORS(uint8_t* buffer, primary_HV_ERRORS* primary_hv_errors);

/* primary_TS_STATUS */
typedef struct __is_packed {
    primary_Ts_Status ts_status;
} primary_TS_STATUS;
static_assert(sizeof(primary_TS_STATUS) == 1, "struct size mismatch");
    
size_t serialize_primary_TS_STATUS(uint8_t* buffer, primary_Ts_Status ts_status);
size_t deserialize_primary_TS_STATUS(uint8_t* buffer, primary_TS_STATUS* primary_ts_status);

/* primary_SET_TS_STATUS */
typedef struct __is_packed {
    primary_Ts_Status_Set ts_status_set;
} primary_SET_TS_STATUS;
static_assert(sizeof(primary_SET_TS_STATUS) == 1, "struct size mismatch");
    
size_t serialize_primary_SET_TS_STATUS(uint8_t* buffer, primary_Ts_Status_Set ts_status_set);
size_t deserialize_primary_SET_TS_STATUS(uint8_t* buffer, primary_SET_TS_STATUS* primary_set_ts_status);

/* primary_STEER_STATUS */
typedef struct __is_packed {
    primary_Traction_Control traction_control;
    primary_Map map;
    bool radio_on;
} primary_STEER_STATUS;
static_assert(sizeof(primary_STEER_STATUS) == 3, "struct size mismatch");
    
size_t serialize_primary_STEER_STATUS(uint8_t* buffer, primary_Traction_Control traction_control, primary_Map map, bool radio_on);
size_t deserialize_primary_STEER_STATUS(uint8_t* buffer, primary_STEER_STATUS* primary_steer_status);

/* primary_SET_CAR_STATUS */
typedef struct __is_packed {
    primary_Car_Status_Set car_status_set;
} primary_SET_CAR_STATUS;
static_assert(sizeof(primary_SET_CAR_STATUS) == 1, "struct size mismatch");
    
size_t serialize_primary_SET_CAR_STATUS(uint8_t* buffer, primary_Car_Status_Set car_status_set);
size_t deserialize_primary_SET_CAR_STATUS(uint8_t* buffer, primary_SET_CAR_STATUS* primary_set_car_status);

/* primary_LV_CURRENT */
typedef struct __is_packed {
    uint8_t current;
} primary_LV_CURRENT;
static_assert(sizeof(primary_LV_CURRENT) == 1, "struct size mismatch");
    
size_t serialize_primary_LV_CURRENT(uint8_t* buffer, uint8_t current);
size_t deserialize_primary_LV_CURRENT(uint8_t* buffer, primary_LV_CURRENT* primary_lv_current);

/* primary_LV_VOLTAGE */
typedef struct __is_packed {
    uint8_t voltage_1;
    uint8_t voltage_2;
    uint8_t voltage_3;
    uint8_t voltage_4;
    uint16_t total_voltage;
} primary_LV_VOLTAGE;
static_assert(sizeof(primary_LV_VOLTAGE) == 6, "struct size mismatch");
    
size_t serialize_primary_LV_VOLTAGE(uint8_t* buffer, uint8_t voltage_1, uint8_t voltage_2, uint8_t voltage_3, uint8_t voltage_4, uint16_t total_voltage);
size_t deserialize_primary_LV_VOLTAGE(uint8_t* buffer, primary_LV_VOLTAGE* primary_lv_voltage);

/* primary_LV_TEMPERATURE */
typedef struct __is_packed {
    uint8_t dcdc_temperature;
    uint8_t __unused_padding_1;
    uint16_t battery_temperature;
} primary_LV_TEMPERATURE;
static_assert(sizeof(primary_LV_TEMPERATURE) == 4, "struct size mismatch");
    
size_t serialize_primary_LV_TEMPERATURE(uint8_t* buffer, uint8_t dcdc_temperature, uint16_t battery_temperature);
size_t deserialize_primary_LV_TEMPERATURE(uint8_t* buffer, primary_LV_TEMPERATURE* primary_lv_temperature);

/* primary_COOLING_STATUS */
typedef struct __is_packed {
    uint8_t hv_fan_speed;
    uint8_t lv_fan_speed;
    uint8_t pump_speed;
} primary_COOLING_STATUS;
static_assert(sizeof(primary_COOLING_STATUS) == 3, "struct size mismatch");
    
size_t serialize_primary_COOLING_STATUS(uint8_t* buffer, uint8_t hv_fan_speed, uint8_t lv_fan_speed, uint8_t pump_speed);
size_t deserialize_primary_COOLING_STATUS(uint8_t* buffer, primary_COOLING_STATUS* primary_cooling_status);

/* primary_HV_CELLS_VOLTAGE */
typedef struct __is_packed {
    uint8_t cell_index;
    uint8_t __unused_padding_1;
    uint16_t voltage_0;
    uint16_t voltage_1;
    uint16_t voltage_2;
} primary_HV_CELLS_VOLTAGE;
static_assert(sizeof(primary_HV_CELLS_VOLTAGE) == 8, "struct size mismatch");
    
size_t serialize_primary_HV_CELLS_VOLTAGE(uint8_t* buffer, uint8_t cell_index, uint16_t voltage_0, uint16_t voltage_1, uint16_t voltage_2);
size_t deserialize_primary_HV_CELLS_VOLTAGE(uint8_t* buffer, primary_HV_CELLS_VOLTAGE* primary_hv_cells_voltage);

/* primary_HV_CELLS_TEMP */
typedef struct __is_packed {
    uint8_t cell_index;
    uint8_t temp_0;
    uint8_t temp_1;
    uint8_t temp_2;
    uint8_t temp_3;
    uint8_t temp_4;
    uint8_t temp_5;
    uint8_t temp_6;
} primary_HV_CELLS_TEMP;
static_assert(sizeof(primary_HV_CELLS_TEMP) == 8, "struct size mismatch");
    
size_t serialize_primary_HV_CELLS_TEMP(uint8_t* buffer, uint8_t cell_index, uint8_t temp_0, uint8_t temp_1, uint8_t temp_2, uint8_t temp_3, uint8_t temp_4, uint8_t temp_5, uint8_t temp_6);
size_t deserialize_primary_HV_CELLS_TEMP(uint8_t* buffer, primary_HV_CELLS_TEMP* primary_hv_cells_temp);

/* primary_SET_CHG_POWER */
typedef struct __is_packed {
    uint16_t current;
    uint16_t voltage;
} primary_SET_CHG_POWER;
static_assert(sizeof(primary_SET_CHG_POWER) == 4, "struct size mismatch");
    
size_t serialize_primary_SET_CHG_POWER(uint8_t* buffer, uint16_t current, uint16_t voltage);
size_t deserialize_primary_SET_CHG_POWER(uint8_t* buffer, primary_SET_CHG_POWER* primary_set_chg_power);

/* primary_CHG_STATUS */
typedef struct __is_packed {
    primary_Status status;
} primary_CHG_STATUS;
static_assert(sizeof(primary_CHG_STATUS) == 1, "struct size mismatch");
    
size_t serialize_primary_CHG_STATUS(uint8_t* buffer, primary_Status status);
size_t deserialize_primary_CHG_STATUS(uint8_t* buffer, primary_CHG_STATUS* primary_chg_status);

/* primary_SET_CHG_STATUS */
typedef struct __is_packed {
    primary_Status status;
} primary_SET_CHG_STATUS;
static_assert(sizeof(primary_SET_CHG_STATUS) == 1, "struct size mismatch");
    
size_t serialize_primary_SET_CHG_STATUS(uint8_t* buffer, primary_Status status);
size_t deserialize_primary_SET_CHG_STATUS(uint8_t* buffer, primary_SET_CHG_STATUS* primary_set_chg_status);

/* primary_CHG_SETTINGS */
typedef struct __is_packed {
    uint8_t v_cutoff;
} primary_CHG_SETTINGS;
static_assert(sizeof(primary_CHG_SETTINGS) == 1, "struct size mismatch");
    
size_t serialize_primary_CHG_SETTINGS(uint8_t* buffer, uint8_t v_cutoff);
size_t deserialize_primary_CHG_SETTINGS(uint8_t* buffer, primary_CHG_SETTINGS* primary_chg_settings);
#endif

#ifdef __cplusplus
}
#endif