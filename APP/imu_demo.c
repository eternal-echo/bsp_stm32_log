
#include "cmsis_os2.h"
#include "driver_mpu6050_basic.h"

#define LOG_TAG "imu_demo"
#define LOG_LVL ELOG_LVL_VERBOSE
#include "util.h"

void imu_demo() {
    uint8_t res;
    mpu6050_address_t addr;

    float g[3];
    float dps[3];
    float degrees;

    /* init */
    addr = MPU6050_ADDRESS_AD0_LOW;
    res = mpu6050_basic_init(addr);
    if (res != 0)
    {
        /* handle error */
        log_e("init failed.\n");
    }


    /* test */
    /* 循环读取加速度、陀螺仪和温度数据 */
    for (uint32_t i = 0; i < 10; i++) // 读取 10 次
    {
        /* 读取加速度和陀螺仪数据 */
        res = mpu6050_basic_read(g, dps);
        if (res != 0)
        {
            log_e("read failed.\n");
            break;
        }

        /* 读取温度数据 */
        res = mpu6050_basic_read_temperature(&degrees);
        if (res != 0)
        {
            log_e("read temperature failed.\n");
            break;
        }

        /* 输出读取的数据 */
        log_i("mpu6050: 第 %d 次读取\n", i + 1);
        log_i("acc: x = %0.2fg, y = %0.2fg, z = %0.2fg\n", g[0], g[1], g[2]);
        log_i("gyr: x = %0.2fdps, y = %0.2fdps, z = %0.2fdps\n", dps[0], dps[1], dps[2]);
        log_i("t: %0.2f°C\n", degrees);

        /* 延迟 1 ms */
        delay_ms(1);
    }

    /* 释放资源 */
    mpu6050_basic_deinit();
}