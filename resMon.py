#import libraries (psutil for monitoring PC and pyserial for sending data throught serial interface
import psutil
import serial
import shutil
import platform
import sys
import subprocess

import GPUtil
#Drive's

DD1=sys.argv[1]
DD2=sys.argv[2]
#pySerial settings
ser = serial.Serial()                                           #make instance of Serial
ser.baudrate = 9600                                             #set baud to 9600 (9600b/s)
ser.port = sys.argv[3]                                          #"/dev/cu.usbserial-550D0034871" replace COM6 with your Arduino port; set serial port
ser.open()                                                      #open the port

cpu_tmp=""
#system info that doesn´t need to be refreshed
osinf=str(platform.platform(terse=True))
osinf=osinf[0:10]
total, used, free = shutil.disk_usage(DD1)
total2, used2, free2 = shutil.disk_usage(DD2)

#get number of PHYSICAL cores
coreCount = psutil.cpu_count(logical = False)   
cores = str(coreCount)
if len(cores)==4:
    cores=cores+"C"                             
if len(cores)==3:
    cores="|"+cores+"C"
if len(cores)==2:
    cores="||"+cores+"C"
if len(cores)==1:
    cores="|||"+cores+"C"

#get total memory size
totalMem = round(psutil.virtual_memory().total / 1073741824)   
totalMem=totalMem
if totalMem <=9 :
    totalMemStr ="|||"+str(totalMem)+"G"                
if totalMem >= 10 and totalMem <= 99:
    totalMemStr = "||"+str(totalMem)+"G" 
if totalMem >= 100 and totalMem <= 999:
    totalMemStr = "|"+str(totalMem)+"G"
if totalMem >= 1000 and totalMem <= 9999:
    totalMemStr = str(totalMem)+"G"


#infinite loop, we don´t want to stop this program..
while(1):                                                      
    cpu = psutil.cpu_percent(interval=1.2)
    mem = psutil.virtual_memory().percent
    sdd = psutil.disk_usage(DD1).percent
    hdd = psutil.disk_usage(DD2).percent

    if cpu < 10:
        cpuStr = "||" + str(cpu)
    elif cpu < 100:
        cpuStr = "|" + str(cpu)
    else:
        cpuStr = str(cpu)

    if mem < 10:
        memStr = "||" + str(mem)
    elif mem < 100:
        memStr = "|" + str(mem)
    else:
        memStr = str(mem)

    if hdd < 10:
        hddStr = "||" + str(hdd)
    elif hdd < 100:
        hddStr = "|" + str(hdd)
    else:
        hddStr = str(hdd)

    if sdd < 10:
        sddStr = "||" + str(sdd)
    elif sdd < 100:
        sddStr = "|" + str(sdd)
    else:
        sddStr = str(sdd)
    
    hdd1t = "%.2f" % (total/1000**4)
    hdd1t = str(hdd1t) + "TB"

    hdd2t = "%.2f" % (total2/1000**4)
    hdd2t = str(hdd2t) + "TB"

    ctmac="mac" in osinf 
    ctwin="Win" in osinf 

    if ctmac:
        result=subprocess.run(['osx-cpu-temp'], stdout=subprocess.PIPE)
        result=result.stdout.decode('utf-8')
        cpu_tmp=str(result[0:3])
        
    if ctwin:
        gpu=GPUtil.getGPUs()[0]
        result=str(gpu.temperature)
        cpu_tmp=result[0:3]

    serialDataStr = cpuStr + memStr + sddStr + hddStr + cores + totalMemStr + hdd1t + hdd2t + osinf + cpu_tmp
    serialDataBytes = serialDataStr.encode("UTF-8")

    print(serialDataBytes)
    #print(len(serialDataBytes))
    ser.write(serialDataBytes)

ser.close()

