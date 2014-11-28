from Tkinter import *
import serial
import sys


slow_speed = 500 # rpm
fast_speed = 2000 # rpm

#rev_time = delay_time * (1/8e6 * 4) * 12 * 6 + (30 * 6 * 20e-6) # seconds
#rpm = 60 / rev_time

# rev_time = 60 / rpm
# delay_time = (60 / rpm -  (30 * 6 * 20e-6)) / ((1/8e6 * 4) * 12 * 6 )

class App:
    def __init__(self, tkroot, ser):
        self.tkroot = tkroot
        self.ser = ser
        self.ser.flush()
        
        # Create the user interface
        for i in range(2):
            self.tkroot.rowconfigure(i, weight = 1)
        for i in range(3):
            self.tkroot.columnconfigure(i, weight = 1)
        
        self.start_button = Button(self.tkroot, text="Start", command = self.start)
        self.start_button.grid(row = 0, column = 0, sticky = N+S+E+W)
        self.stop_button = Button(self.tkroot, text="Stop", command = self.stop, state = DISABLED)
        self.stop_button.grid(row = 0, column = 1, sticky = N+S+E+W)
        Button(self.tkroot, text="Quit", command = self.quit).grid(row = 0, column = 2,
                                                                   sticky = N+S+E+W)
        
        Label(self.tkroot, text="RPM:").grid(row = 1, column = 1)
        self.set_slider = Scale(self.tkroot, from_=slow_speed, to=fast_speed,
                                width = 20, length = 500,
                                orient=HORIZONTAL, command = self.set_speed)
        self.set_slider.grid(row = 2, column = 0, columnspan = 3, sticky = N+S+E+W)
        
        self.stop()
        
        self.update()
    
    def start(self):
        self.running = True
        self.set_speed(slow_speed)
        self.set_slider.config(state = NORMAL, troughcolor = "#aaa")
        ser.write("j\n")
        self.start_button.config(state = DISABLED)
        self.stop_button.config(state = NORMAL)
    
    def stop(self):
        self.running = False
        self.set_slider.set(slow_speed)
        self.set_slider.config(state = DISABLED, troughcolor = "#fff")
        self.start_button.config(state = NORMAL)
        self.stop_button.config(state = DISABLED)
        ser.write("s\n")
    
    def set_speed(self, value):
        if self.running:
            delay_time = int((60.0 / int(value) - (30 * 6 * 20e-6)) / (4/8e6 * 12 * 6))
            print delay_time
            ser.write(str(delay_time) + "\n")
        
    def quit(self):
        self.stop()
        self.tkroot.destroy()
    
    def update(self):
        self.tkroot.after(100, self.update)


#
#  check command line arguments
#
if (len(sys.argv) != 2):
   print "command line: ui.py serial_port"
   sys.exit()
port = sys.argv[1]
#
# open serial port
#
ser = serial.Serial(port, 9600)
ser.setDTR()

tkroot = Tk()
tkroot.title('ESC control panel')
app = App(tkroot, ser)
tkroot.mainloop()