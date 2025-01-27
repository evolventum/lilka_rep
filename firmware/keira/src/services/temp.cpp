#include "temp.h"
#include "lilka.h"
#include "driver/temp_sensor.h"

TemperatureSensor::TemperatureSensor() : Service("temperature") {
    // lilka::serial_log("Start service");
    temp_sensor_config_t temp_sensor = TSENS_CONFIG_DEFAULT();
    temp_sensor.dac_offset = TSENS_DAC_L2;  // TSENS_DAC_L2 is default; L4(-40°C ~ 20°C), L2(-10°C ~ 80°C), L1(20°C ~ 100°C), L0(50°C ~ 125°C)
    temp_sensor_set_config(temp_sensor);
    temp_sensor_start();
}

void TemperatureSensor::run() {  
    while (1) {
#ifdef TEMP_SENS_SERIAL  
        float result_float = 0;
        temp_sensor_read_celsius(&result_float);
        int result_int = (int)result_float;
        std::string result_str = std::to_string(result_int);
        char const *pchar = result_str.c_str(); 
        lilka::serial_log(pchar, "C");
#endif
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

int TemperatureSensor::temp_now() {
    float result_float = 0;
    temp_sensor_read_celsius(&result_float);
    int result_int = (int)result_float;
    return result_int;
}

