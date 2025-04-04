.. _bldc_square_wave_inject_hfi:

BLDC HFI 高频注入
==========================

概述
------

**bldc_hfi** 工程展示了直流无刷电机的无感转速控制。
- 电机控制算法为 **空间矢量算法**

- 无感控制算法为 **方波高频注入算法**

- 无感控制低转速性能


.. note::

   - 这个demo仅用于实验目的，由于不同硬件之间的差异，可能会出现一些问题。


配置
------

- 本例程电机使用的是时代超群的 **57B3C0730**  无刷电机。

- 板子设置参考开发板文档 :ref:`Motor Pin <board_resource>` 相关内容

- 确保开发板供电充足，如果供电不足请去掉USB-HUB并插入多个USB数据线进行供电

- 完成上述过程后，给驱动板上电观察电流无异常后，给核心板上电，再次确认电流无异常后，就可以烧录程序，观察运行现象。

运行现象
------------

电机会以 1 r/s的极低速度运行。

串口输出如下:


.. code-block:: console

   Motor Inject demo.



.. warning::

   - 电机上电后首先要完成磁极辨识操作，这时候请不要干预电机运行，否则会产生异常

   - 电机运行时，请时刻注意电流大小，如果发生异常，请随时准备切断电源。

