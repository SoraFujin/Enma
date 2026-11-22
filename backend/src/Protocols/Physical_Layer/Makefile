
MCU        := atmega328p
F_CPU      := 16000000UL
PROGRAMMER := arduino
BAUD       := 115200

RECEIVER_PORT    ?= /dev/ttyACM1
TRANSMITTER_PORT ?= /dev/ttyACM0

CC      := avr-gcc
OBJCOPY := avr-objcopy
AVRDUDE := avrdude

CFLAGS := -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra \
          -Iinclude

OUTPUT := output

COMMON_SRC := src/gpio_setup.c src/utils.c

.PHONY: all help clean receiver transmitter flash-receiver flash-transmitter

all: receiver transmitter

help:
	@echo "Physical Layer - Build and Flash Commands"
	@echo ""
	@echo "Build:"
	@echo "  make"
	@echo "  make receiver"
	@echo "  make transmitter"
	@echo ""
	@echo "Flash:"
	@echo "  make flash-receiver"
	@echo "  make flash-transmitter"
	@echo ""
	@echo "Clean:"
	@echo "  make clean"

$(OUTPUT):
	mkdir -p $(OUTPUT)

receiver: $(OUTPUT)/receiver.hex

transmitter: $(OUTPUT)/transmitter.hex

$(OUTPUT)/receiver.elf: firmware/receiver/main.c src/receiver.c $(COMMON_SRC) | $(OUTPUT)
	$(CC) $(CFLAGS) $^ -o $@

$(OUTPUT)/transmitter.elf: firmware/transmitter/main.c src/transmitter.c $(COMMON_SRC) | $(OUTPUT)
	$(CC) $(CFLAGS) $^ -o $@

$(OUTPUT)/receiver.hex: $(OUTPUT)/receiver.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(OUTPUT)/transmitter.hex: $(OUTPUT)/transmitter.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

flash-receiver: $(OUTPUT)/receiver.hex
	$(AVRDUDE) -v -p $(MCU) -c $(PROGRAMMER) \
		-P $(RECEIVER_PORT) -b $(BAUD) -D \
		-U flash:w:$<:i

flash-transmitter: $(OUTPUT)/transmitter.hex
	$(AVRDUDE) -v -p $(MCU) -c $(PROGRAMMER) \
		-P $(TRANSMITTER_PORT) -b $(BAUD) -D \
		-U flash:w:$<:i

clean:
	rm -f $(OUTPUT)/receiver.elf $(OUTPUT)/receiver.hex
	rm -f $(OUTPUT)/transmitter.elf $(OUTPUT)/transmitter.hex

