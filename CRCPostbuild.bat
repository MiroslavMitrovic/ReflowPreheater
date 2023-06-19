::SCRIPT FOR FILLING THE IMAGE AND PERFORMING THE CRC32 CALCULATION# 

@echo ON
::# Get the image data 
::set PATH="d:/D_Projects_10102022/projects/STM32CubeIDE/workspace_1.9.0/ReflowPreheater/"
set IMAGE_NAME=.\ReflowPreheater.srec
set IMAGE_START_ADDRESS=0x08040000
set IMAGE_END_ADDRESS=0x0805FFFC
set IMAGE_END_ADDRESS_DATA=0x0804F264
::srec_cat.exe %IMAGE_NAME% -fill 0xFF 0x08040000 0x0805FFFC -crc32-b-e 0x0805FFFC  -o ReflowPreheater_crc.srec
::srec_cat.exe  %IMAGE_NAME% -fill 0xFF %IMAGE_START_ADDRESS% %IMAGE_END_ADDRESS% -crc32-b-e  0x0805FFFC -CCITT -o .\ReflowPreheater_crc.srec
srec_cat.exe  %IMAGE_NAME% -fill 0xFF %IMAGE_START_ADDRESS% %IMAGE_END_ADDRESS% -crc32-b-e  %IMAGE_END_ADDRESS% -CCITT -o .\ReflowPreheater_crc.srec

