.. _qei:

QEI
======

概述
------

**Qei** 工程主要演示电机编码器触发 **qei** 中断后，通过串口将MCU采集到的一些编码器数据打印出来。

- 编码器中断

- 编码器`z\phase\speed\timer`寄存器的数据读取

配置
------

- 安装串口终端，查看 :ref:`板子信息 <board_resource>` 并配置串口终端参数

- 电机使用的是雷赛智能 **BLM57050-1000**  无刷电机，电机具体参数请参考`雷赛智能官网 <https://leisai.com/>`_。

- 点击查看  :ref:`DRV-LV50A-MP1907电机驱动板 <drv_lv50a_mp1907>`  章节并进行配置

运行现象
------------

- 上电后，打开串口终端，打印启动信息。每转动电机轴到一定角度，就会触发编码器中断并依次打印如下信息，数据随着转动的快慢和方向变化，数据的具体含义请参考用户手册。


.. code-block:: console

   > z: 0xffffff9c
   > phase: 0xc200014d
   > speed: 0xa0000000
   > timer: 0xa8d08799

