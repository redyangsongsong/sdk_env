.. _xpi_nor_api_demo:

XPI NOR API 示例
============================

概述
------

本示例提供了如下功能：
- 对FLASH最后一个扇区进行擦除、写和验证

- 对整个FLASH区间做压力测试：

  - 全FLASH擦除

  - 全FLASH写入

  - 全FLASH读回

- 演示使用命令序列和基本XPI API 与FLASH通信

硬件设置
------------

无特殊设置

运行现象
------------

当工程正确运行后，串口终端会打印如下菜单，用户可通过串口输入其中的选项来执行相应的功能

.. code-block:: console

   XPI NOR demo
   ----------------------------------------
    1 - Test FLASH at the last Sector
    2 - Stress test on the FLASH
        NOTE: This case cannot be tested on flash_xip build
    3 - Access FLASH via instruction sequence and basic XPI API
    Others - Show menu
