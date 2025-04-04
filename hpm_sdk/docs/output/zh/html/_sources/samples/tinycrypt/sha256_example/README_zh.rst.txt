.. _sha256_algorithm:

SHA256算法
================

概述
------

**sha256_example** 示例工程展示了SHA256算法的实现。
- 此工程的解密算法采用NIST SHA256法完成模块加解密测试。

硬件设置
------------

- 无特殊设置

运行现象
------------

当工程正确运行后，串口终端会输出如下信息：

.. code-block:: console

   tc_start() - Performing SHA256 tests (NIST tests vectors):
   SHA256 test #1:
   ===================================================================
   PASS - test_1.
   SHA256 test #2:
   ===================================================================
   PASS - test_2.
   SHA256 test #3:
   ===================================================================
   PASS - test_3.
   SHA256 test #4:
   ===================================================================
   PASS - test_4.
   SHA256 test #5:
   ===================================================================
   PASS - test_5.
   SHA256 test #6:
   ===================================================================
   PASS - test_6.
   SHA256 test #7:
   ===================================================================
   PASS - test_7.
   SHA256 test #8:
   ===================================================================
   PASS - test_8.
   SHA256 test #9:
   ===================================================================
   PASS - test_9.
   SHA256 test #10:
   ===================================================================
   PASS - test_10.
   SHA256 test #11:
   ===================================================================
   PASS - test_11.
   SHA256 test #12:
   ===================================================================
   PASS - test_12.
   SHA256 test #13:
   SHA256 test #14:
   ===================================================================
   PASS - test_14.
   All SHA256 tests succeeded!
   ===================================================================
   PASS - main.
   ===================================================================
   PROJECT EXECUTION SUCCESSFUL



.. note::

   test_14需要花费数分钟时间运行，请耐心等待

