DEVICE     = attiny85           # See avr-help for all possible devices
CLOCK      = 16500000           # 16Mhz
OBJECTS    = main.o usbdrv.o usbdrvasm.o osccal.o TinyWireM.o USI_TWI_Master.o # Add more objects for each .c file here

UPLOAD = micronucleus --run
COMPILE = avr-gcc -Iusb -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)
COMPILEXX = avr-g++ -Iusb -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

# symbolic targets:
all:	main.hex

main.o: main.c
	$(COMPILE) -c $< -o $@

usbdrv.o: usb/usbdrv.c
	$(COMPILE) -c $< -o $@

usbdrvasm.o: usb/usbdrvasm.S
	$(COMPILE) -c $< -o $@

osccal.o: usb/osccal.c
	$(COMPILE) -c $< -o $@

TinyWireM.o: i2c/TinyWireM.c
	$(COMPILE) -c $< -o $@

USI_TWI_Master.o: i2c/USI_TWI_Master.c
	$(COMPILE) -c $< -o $@

flash:	all
	$(UPLOAD) main.hex

clean:
	rm -f main.hex main.elf $(OBJECTS)

main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(DEVICE) main.elf
