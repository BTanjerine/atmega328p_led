default: build 
	
build: 
	# compile c code 
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o first.o first.c   
	# convert to binary
	avr-gcc -o first.bin first.o

burn: 	build 
	# convert to hex for arduino board
	avr-objcopy -O ihex -R .eeprom first.bin first.hex
	#send the hex file to the rom on the board
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P  /dev/ttyUSB0 -b 115200 -U flash:w:first.hex
