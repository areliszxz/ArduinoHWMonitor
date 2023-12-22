import flet as ft
import psutil
import serial
import shutil
import platform
import sys
import subprocess
import threading


def main(page):
    page.window_height=500
    page.window_max_width=500
    page.window_resizable=False
    
    dd1_dir_input = ft.TextField(label="HDD1" , autofocus=True, value="/" )
    dd2_dir_input = ft.TextField(label="HDD2", value="/")
    port_str_input = ft.TextField(label="PORT", value="/dev/cu.usbserial-550D0034871")
    status_input = ft.TextField(label="Status:", value="OFF", read_only=True)
    term = ft.TextField(label="Term:", value="...",max_lines=2, min_lines=2)
    greetings = ft.Column()

    def bs_dismissed(e):
        print("Pass!")

    def show_bs(e):
        bs.open = True
        bs.update()

    def close_bs(e):
        bs.open = False
        bs.update()

    bs = ft.BottomSheet(    
        ft.Container(
            ft.Column(
                [
                    ft.Text("  Informacion en processo de envio.  "),
                    ft.ElevatedButton("OK", on_click=close_bs),
                ],
                tight=True,
                alignment="center",
                horizontal_alignment="center",
            ),
            padding=20,
        ),
        open=False,
        on_dismiss=bs_dismissed,
    )
    page.overlay.append(bs)

    def btn_click(e):
        run_press(e)
        page.update()
 
    def run_press(e): 
        stats=str(status_input.value)
        print("RUNC"+"-->"+stats)
        if stats=="OFF":
            status_input.value="ON"
            print("Enviado")
            page.update()
            proceso = threading.Thread (target=init_main(dd1_dir_input.value,dd2_dir_input.value,port_str_input.value))
            proceso.start()

        if stats=="ON":
            #proceso.join()
            print("Enviando en proceso")
            show_bs(e)
            page.update()
        

    def init_main(dd1, dd2, port):
        #Drive's
        DD1=str(dd1)
        DD2=str(dd2)
        #pySerial settings
        ser = serial.Serial(timeout=0)                                           #make instance of Serial
        ser.baudrate = 9600                                             #set baud to 9600 (9600b/s)
        ser.port = port                                    #"/dev/cu.usbserial-550D0034871" replace COM6 with your Arduino port; set serial port
        ser.open()                                                      #open the port
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
            ctwin="win" in osinf 
            if ctmac:
                result = subprocess.run(['osx-cpu-temp'], stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
                result=result.stdout.decode('utf-8')
                cputs=str(result[0:2])
                
            if ctwin:
                result = subprocess.run(['osx-cpu-temp'], stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
                result=result.stdout.decode('utf-8')
                cputs=str(result[0:2])

            if  cputs=="":
                cputs="0.00"
                        
            serialDataStr = cpuStr + memStr + sddStr + hddStr + cores + totalMemStr + hdd1t + hdd2t + osinf + cputs
            serialDataBytes = serialDataStr.encode("UTF-8")
            #print(serialDataBytes)
            #print(len(serialDataBytes))
            ser.write(serialDataBytes)
            term.value=serialDataStr
            page.update()
        ser.close()


    page.add(
        dd1_dir_input,
        dd2_dir_input,  
        port_str_input,
        status_input,
        term,
        ft.ElevatedButton("Run!", on_click=btn_click),
    )

    
ft.app(target=main)