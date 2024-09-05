---
title: README.md
---
# MPU6050驱动介绍

MPU6050是一个常见的六轴传感器（3轴加速度计和3轴陀螺仪），用于测量物体的加速度和角速度。本库`mpu6050`基于I2C接口，用于与MPU6050芯片进行通信并获取传感器数据。该库提供了丰富的接口，方便用户进行初始化、配置和数据采集，支持FIFO、DMP（Digital Motion Processor）等高级功能。

#### 库的基本流程

1. **初始化芯片**： 通过调用`mpu6050_init`函数初始化芯片，设置I2C地址、配置时钟源、加速度和陀螺仪量程等参数。

2. **读取传感器数据**： 调用`mpu6050_read`函数读取加速度计和陀螺仪的原始数据，并将其转换为物理单位（加速度：g，陀螺仪：°/s）。

3. **高级功能**： 通过DMP固件可以启用更多复杂功能，比如步伐计数、手势识别等。调用`mpu6050_dmp_load_firmware`加载固件后，用户可以启用和配置这些功能。

4. **配置参数**： 支持配置多种参数，比如低通滤波器、I2C模式、FIFO使能等，用户可以根据应用场景灵活调整。

# API说明

### 1\. **设备初始化与管理接口**

这些接口用于 MPU6050 设备的初始化、关闭和状态检查，适用于所有基于 MPU6050 的项目：

#### 1.1. `` `  ``<SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="10648:2:2" line-data="uint8_t mpu6050_info(mpu6050_info_t *info)">`mpu6050_info`</SwmToken>

- **功能**：获取芯片的信息。

- **使用场景**：用于获取 MPU6050 的基本信息，如芯片名称、制造商、供电电压等。

#### 1.2. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="3717:2:2" line-data="uint8_t mpu6050_init(mpu6050_handle_t *handle)">`mpu6050_init`</SwmToken>

- **功能**：初始化 MPU6050 传感器。

- **使用场景**：用于在开始使用 MPU6050 时调用，以配置初始设置。

#### 1.3. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="3837:2:2" line-data="uint8_t mpu6050_deinit(mpu6050_handle_t *handle)">`mpu6050_deinit`</SwmToken>

- **功能**：关闭 MPU6050 传感器。

- **使用场景**：用于在不再使用 MPU6050 时调用，释放资源并进入休眠模式。

#### 1.4. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="3672:2:2" line-data="uint8_t mpu6050_set_addr_pin(mpu6050_handle_t *handle, mpu6050_address_t addr_pin)">`mpu6050_set_addr_pin`</SwmToken> / <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="3693:2:2" line-data="uint8_t mpu6050_get_addr_pin(mpu6050_handle_t *handle, mpu6050_address_t *addr_pin)">`mpu6050_get_addr_pin`</SwmToken>

- **功能**：设置或获取 MPU6050 的 I2C 地址。

- **使用场景**：当设备需要指定特定 I2C 地址时使用。

#### 1.5. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="4170:2:2" line-data="uint8_t mpu6050_irq_handler(mpu6050_handle_t *handle)">`mpu6050_irq_handler`</SwmToken>

- **功能**：中断处理函数。

- **使用场景**：当 MPU6050 发生中断时，用于处理中断信号。

### 2\. **数据读取与转换接口**

这些接口用于读取 MPU6050 中的加速度、陀螺仪数据和温度信息：

#### 2.1. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="3890:2:2" line-data="uint8_t mpu6050_read(mpu6050_handle_t *handle, int16_t (*accel_raw)[3], float (*accel_g)[3],">`mpu6050_read`</SwmToken>

- **功能**：读取加速度和陀螺仪数据。

- **使用场景**：需要获取实时传感器数据时使用。

#### 2.2. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="4133:2:2" line-data="uint8_t mpu6050_read_temperature(mpu6050_handle_t *handle, int16_t (*raw), float *degrees)">`mpu6050_read_temperature`</SwmToken>

- **功能**：读取传感器的温度值。

- **使用场景**：当需要读取传感器的温度信息时使用。

#### 2.3. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="7428:2:2" line-data="uint8_t mpu6050_motion_threshold_convert_to_register(mpu6050_handle_t *handle, float mg, uint8_t *reg)">`mpu6050_motion_threshold_convert_to_register`</SwmToken> / <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="7455:2:2" line-data="uint8_t mpu6050_motion_threshold_convert_to_data(mpu6050_handle_t *handle, uint8_t reg, float *mg)">`mpu6050_motion_threshold_convert_to_data`</SwmToken>

- **功能**：将运动阈值转换为寄存器数据或从寄存器数据转换为运动阈值。

- **使用场景**：当需要设置或读取运动检测阈值时使用。

#### 2.4. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="7552:2:2" line-data="uint8_t mpu6050_motion_duration_convert_to_register(mpu6050_handle_t *handle, uint8_t ms, uint8_t *reg)">`mpu6050_motion_duration_convert_to_register`</SwmToken> / <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="7579:2:2" line-data="uint8_t mpu6050_motion_duration_convert_to_data(mpu6050_handle_t *handle, uint8_t reg, uint8_t *ms)">`mpu6050_motion_duration_convert_to_data`</SwmToken>

- **功能**：将运动持续时间转换为寄存器数据或从寄存器数据转换为时间。

- **使用场景**：用于设置或读取运动检测的持续时间。

### 3\. **FIFO 缓冲区管理**

FIFO 用于存储传感器的数据，这些接口负责管理 FIFO 功能：

#### 3.1. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="4242:2:2" line-data="uint8_t mpu6050_set_fifo(mpu6050_handle_t *handle, mpu6050_bool_t enable)">`mpu6050_set_fifo`</SwmToken> / <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="4287:2:2" line-data="uint8_t mpu6050_get_fifo(mpu6050_handle_t *handle, mpu6050_bool_t *enable)">`mpu6050_get_fifo`</SwmToken>

- **功能**：启用或禁用 FIFO 功能。

- **使用场景**：用于控制是否启用 FIFO 数据存储功能。

#### 3.2. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="4439:2:2" line-data="uint8_t mpu6050_fifo_reset(mpu6050_handle_t *handle)">`mpu6050_fifo_reset`</SwmToken>

- **功能**：重置 FIFO。

- **使用场景**：当需要清除 FIFO 数据时使用。

#### 3.3. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="5296:2:2" line-data="uint8_t mpu6050_fifo_get(mpu6050_handle_t *handle, uint8_t *buf, uint16_t len)">`mpu6050_fifo_get`</SwmToken>

- **功能**：读取 FIFO 中的数据。

- **使用场景**：从 FIFO 中读取存储的传感器数据。

### 4\. **传感器配置**

这些接口用于配置 MPU6050 的各项参数：

#### 4.1. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="4764:2:2" line-data="uint8_t mpu6050_set_clock_source(mpu6050_handle_t *handle, mpu6050_clock_source_t clock_source)">`mpu6050_set_clock_source`</SwmToken> / <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="4809:2:2" line-data="uint8_t mpu6050_get_clock_source(mpu6050_handle_t *handle, mpu6050_clock_source_t *clock_source)">`mpu6050_get_clock_source`</SwmToken>

- **功能**：设置或获取时钟源。

- **使用场景**：配置 MPU6050 的时钟源时使用。

#### 4.2. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="5564:2:2" line-data="uint8_t mpu6050_set_low_pass_filter(mpu6050_handle_t *handle, mpu6050_low_pass_filter_t filter)">`mpu6050_set_low_pass_filter`</SwmToken> / <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="5609:2:2" line-data="uint8_t mpu6050_get_low_pass_filter(mpu6050_handle_t *handle, mpu6050_low_pass_filter_t *filter)">`mpu6050_get_low_pass_filter`</SwmToken>

- **功能**：设置或获取低通滤波器。

- **使用场景**：当需要降低噪声时，设置滤波器频率。

#### 4.3. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="5412:2:2" line-data="uint8_t mpu6050_set_sample_rate_divider(mpu6050_handle_t *handle, uint8_t d)">`mpu6050_set_sample_rate_divider`</SwmToken> / <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="5447:2:2" line-data="uint8_t mpu6050_get_sample_rate_divider(mpu6050_handle_t *handle, uint8_t *d)">`mpu6050_get_sample_rate_divider`</SwmToken>

- **功能**：设置或获取采样率分频器。

- **使用场景**：调整传感器数据采样率时使用。

#### 4.4. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="5730:2:2" line-data="uint8_t mpu6050_set_gyroscope_range(mpu6050_handle_t *handle, mpu6050_gyroscope_range_t range)">`mpu6050_set_gyroscope_range`</SwmToken> / <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="5775:2:2" line-data="uint8_t mpu6050_get_gyroscope_range(mpu6050_handle_t *handle, mpu6050_gyroscope_range_t *range)">`mpu6050_get_gyroscope_range`</SwmToken>

- **功能**：设置或获取陀螺仪的量程。

- **使用场景**：根据应用需要，配置不同的陀螺仪量程。

#### 4.5. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="5896:2:2" line-data="uint8_t mpu6050_set_accelerometer_range(mpu6050_handle_t *handle, mpu6050_accelerometer_range_t range)">`mpu6050_set_accelerometer_range`</SwmToken> / <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="5941:2:2" line-data="uint8_t mpu6050_get_accelerometer_range(mpu6050_handle_t *handle, mpu6050_accelerometer_range_t *range)">`mpu6050_get_accelerometer_range`</SwmToken>

- **功能**：设置或获取加速度计的量程。

- **使用场景**：根据应用需要，调整加速度计的量程。

### 5\. **自测功能**

这些接口用于运行设备的自检或测试：

#### 5.1. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="7659:2:2" line-data="uint8_t mpu6050_self_test(mpu6050_handle_t *handle, int32_t gyro_offset_raw[3], int32_t accel_offset_raw[3])">`mpu6050_self_test`</SwmToken>

- **功能**：运行自检功能，检查传感器是否正常工作。

- **使用场景**：初始化时或定期进行自检，确保设备正常运行。

### 6\. **中断管理**

这些接口用于配置 MPU6050 的中断功能：

#### 6.1. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="6637:2:2" line-data="uint8_t mpu6050_set_interrupt(mpu6050_handle_t *handle, mpu6050_interrupt_t type, mpu6050_bool_t enable)">`mpu6050_set_interrupt`</SwmToken> / <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="6683:2:2" line-data="uint8_t mpu6050_get_interrupt(mpu6050_handle_t *handle, mpu6050_interrupt_t type, mpu6050_bool_t *enable)">`mpu6050_get_interrupt`</SwmToken>

- **功能**：设置或获取中断类型（如运动检测中断、FIFO 溢出中断等）。

- **使用场景**：当需要配置 MPU6050 的中断响应时使用。

#### 6.2. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="6062:2:2" line-data="uint8_t mpu6050_set_interrupt_level(mpu6050_handle_t *handle, mpu6050_pin_level_t level)">`mpu6050_set_interrupt_level`</SwmToken> / <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="6107:2:2" line-data="uint8_t mpu6050_get_interrupt_level(mpu6050_handle_t *handle, mpu6050_pin_level_t *level)">`mpu6050_get_interrupt_level`</SwmToken>

- **功能**：设置或获取中断电平（高电平或低电平触发）。

- **使用场景**：当需要设置中断信号的触发电平时使用。

#### 6.3. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="6144:2:2" line-data="uint8_t mpu6050_set_interrupt_pin_type(mpu6050_handle_t *handle, mpu6050_pin_type_t type)">`mpu6050_set_interrupt_pin_type`</SwmToken> / <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="6189:2:2" line-data="uint8_t mpu6050_get_interrupt_pin_type(mpu6050_handle_t *handle, mpu6050_pin_type_t *type)">`mpu6050_get_interrupt_pin_type`</SwmToken>

- **功能**：设置或获取中断引脚类型（推挽或开漏）。

- **使用场景**：根据电路设计要求配置中断引脚类型。

### 7\. **DMP 管理**

这些接口用于管理 DMP（Digital Motion Processor）：

#### 7.1. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="836:2:2" line-data="uint8_t mpu6050_dmp_load_firmware(mpu6050_handle_t *handle)">`mpu6050_dmp_load_firmware`</SwmToken>

- **功能**：加载 DMP 固件。

- **使用场景**：当需要启用 DMP 功能时使用。

#### 7.2. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="1008:2:2" line-data="uint8_t mpu6050_dmp_set_pedometer_step_count(mpu6050_handle_t *handle, uint32_t count)">`mpu6050_dmp_set_pedometer_step_count`</SwmToken> / <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="1056:2:2" line-data="uint8_t mpu6050_dmp_get_pedometer_step_count(mpu6050_handle_t *handle, uint32_t *count)">`mpu6050_dmp_get_pedometer_step_count`</SwmToken>

- **功能**：设置或获取计步器步数。

- **使用场景**：当使用 DMP 的计步器功能时使用。

#### 7.3. <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="1383:2:2" line-data="uint8_t mpu6050_dmp_set_tap_time_multi(mpu6050_handle_t *handle, uint16_t ms)">`mpu6050_dmp_set_tap_time_multi`</SwmToken> / <SwmToken path="/BSP/mpu6050/src/driver_mpu6050.c" pos="1430:2:2" line-data="uint8_t mpu6050_dmp_get_tap_time_multi(mpu6050_handle_t *handle, uint16_t *ms)">`mpu6050_dmp_get_tap_time_multi`</SwmToken>

- **功能**：设置或获取多次点击的时间间隔。

- **使用场景**：用于 DMP 手势识别功能时使用。

<SwmMeta version="3.0.0" repo-id="Z2l0aHViJTNBJTNBc3RtMzJfZXhhbXBsZXMlM0ElM0FldGVybmFsLWVjaG8=" repo-name="stm32_examples"><sup>Powered by [Swimm](https://app.swimm.io/)</sup></SwmMeta>
