TARGET=encoder
MCU=atmega32
SOURCES=encoder.c
INCLUDE = /usr/avr/include/
PROGRAMMER=stk600

#Ab hier nichts verändern
OBJECTS=$(SOURCES:.c=.o)
CFLAGS=-c -Os
LDFLAGS=

all: hex eeprom

hex: $(TARGET).hex

eeprom: $(TARGET)_eeprom.hex

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex -j .data -j .text $< $@

$(TARGET)_eeprom.hex: $(TARGET).elf
	avr-objcopy -O ihex -j .eeprom --change-section-lma .eeprom=1 $< $@

$(TARGET).elf: $(OBJECTS)
	avr-g++ $(LDFLAGS) -I$(INCLUDE) -mmcu=$(MCU) $^ -o $@

.c.o:
	avr-g++ $(CFLAGS) -I$(INCLUDE) -mmcu=$(MCU) $< -o $@

size:
	avr-size --mcu=$(MCU) -C $(TARGET).elf

program:
	avrdude -p $(MCU) -c $(PROGRAMMER) -U flash:w:$(TARGET).hex:a

clean_tmp:
	rm -rf *.o
	rm -rf *.elf

clean:
	rm -rf *.o
	rm -rf *.elf
	rm -rf *.hex

.PHONY: clean clean_tmp program
