PROJECT= motor_controller.c
HEX=$(PROJECT).hex
OUT=$(PROJECT).obj

SOURCES=motor_controller.c serial.c hbridge.c
OBJECTS=$(SOURCES:.c=.o)

MMCU=attiny2313
F_CPU = 8000000 # 8 MHz internal RC oscillator
CC=avr-gcc

LINKFLAGS += -Wl,-Map,${PROJECT}.map,--relax,--gc-sections
CFLAGS=-mmcu=$(MMCU) -Wall -Os -DF_CPU=$(F_CPU) $(LINKFLAGS) -Wa,-ahdl=$@.lst -ffunction-sections -fdata-sections


$(HEX): $(OUT)
	avr-objcopy -j .text -O ihex $(OUT) $(HEX)
	avr-size --mcu=$(MMCU) --format=avr $(OUT)

$(OUT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJECTS)


# Dependency tree:
motor_controller.o: motor_controller.c serial.h macros.h
serial.o: serial.c serial.h macros.h
hbridge.o: hbridge.c hbridge.h macros.h

clean:
	rm $(OBJECTS) $(OUT) $(HEX)
################################################################################

program: programmed program-usbtiny
	touch programmed

programmed: $(HEX)

program-bsd: $(HEX)
	avrdude -p attiny2313 -c bsd -U flash:w:$(HEX)

program-dasa: $(HEX)
	avrdude -p attiny2313 -P /dev/ttyUSB0 -c dasa -U flash:w:$(HEX)

program-avrisp2: $(HEX)
	avrdude -p attiny2313 -P usb -c avrisp2 -U flash:w:$(HEX)

program-usbtiny: $(HEX)
	avrdude -p attiny2313 -P usb -c usbtiny -U flash:w:$(HEX)

program-dragon: $(HEX)
	avrdude -p attiny2313 -P usb -c dragon_isp -U flash:w:$(HEX)
