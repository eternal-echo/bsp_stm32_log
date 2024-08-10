# 默认线程
参考[野火的教程](https://doc.embedfire.com/linux/stm32mp1/freertos/zh/latest/application/cpu_usage_rate.html)，打开CubeMX中的RUNTIME_STATS功能。

但是不使用硬件定时器，而是使用[DWT的cycle计数器](https://doc.embedfire.com/mcu/stm32/f103badao/std/zh/latest/book/DWT.html)，这样可以避免硬件定时器的干扰。