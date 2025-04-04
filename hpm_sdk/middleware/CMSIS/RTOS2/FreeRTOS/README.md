# CMSIS-FreeRTOS

This repository contains the CMSIS-RTOS adoption of [FreeRTOS-Kernel Version 10.5.1](https://github.com/FreeRTOS/FreeRTOS-Kernel/releases/download/V10.5.1/FreeRTOS-KernelV10.5.1.zip) as it is released as Software Pack on http://www.keil.com/pack. The [documentation](https://arm-software.github.io/CMSIS-FreeRTOS/) is available under https://arm-software.github.io/CMSIS-FreeRTOS/.

Use *Issues* to provide feedback and report problems for CMSIS FreeRTOS implementation.

Use *main* branch for pull-requests.

Note: Branches *develop* and *master* will be deprecated. Please update your fork and switch to branch *main* to track the latest state of development.

## Directory Structure

| Directory                     | Content                            |                
| ----------------------------- | -----------------------------------|
| CMSIS                         | CMSIS-FreeRTOS related files       |
| CMSIS/RTOS2/FreeRTOS/Config   | CMSIS-FreeRTOS configuration file  |
| CMSIS/RTOS2/FreeRTOS/Examples | CMSIS-FreeRTOS example projects    |
| CMSIS/RTOS2/FreeRTOS/Source   | CMSIS-FreeRTOS source code         |
| Config                        | FreeRTOS Kernel configuration file |
| DoxyGen                       | Source of the documentation        |
| License                       | FreeRTOS Kernel license text file  |
| Source                        | FreeRTOS Kernel source code        |
| Utilities                     | Utility programs                   |

## Generate CMSIS Pack for Release

This GitHub development repository contains all the sources you need to successfully build the pack.

To build the complete pack for installation, the following additional tools are required:
 - **doxygen.exe**    Version: 1.8.6 (Documentation Generator)
 - **mscgen.exe**     Version: 0.20  (Message Sequence Chart Converter)
 - **7z.exe (7-Zip)** Version: 16.04 (File Archiver)
  
Using these tools, you can generate on a Windows PC:
 - **CMSIS-FreeRTOS software pack** using the batch file **gen_pack.bat** (located in ./Utilities). This batch file also
   generates the documentation.
  
 - **CMSIS-FreeRTOS documentation** using the batch file **genDoc.bat** (located in ./Doxygen). 

The file ./DoxyGen/How2Doc.txt describes the rules for creating API documentation.

## License

The FreeRTOS kernel is released under the MIT open source license (see License/license.txt).
