@echo off
echo "Monitor de hardware"
call D:\Mis_Docs\Arduino\ArduinoHWMonitor\run\Scripts\activate.bat & cd D:\Mis_Docs\Arduino\ArduinoHWMonitor\ & python.exe -m resMon.py c: d: COM3
