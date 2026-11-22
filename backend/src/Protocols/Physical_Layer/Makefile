
MCU       := atmega328p
F_CPU     := 16000000UL
PROGRAMMER := arduino
BAUD      := 115200

# Change these if your Arduino ports differ.
RECEIVER_PORT    ?= /dev/ttyACM1
TRANSMITTER_PORT ?= /dev/ttyACM0

CC       := avr-gcc
OBJCOPY  := avr-objcopy
AVRDUDE  := avrdude

CFLAGS   := -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra
OUTPUT   := output

.PHONY: all help clean receiver transmitter flash-receiver flash-transmitter

all: receiver transmitter

help:
	@echo "Physical Layer - Build and Flash Commands"
	@echo ""
	@echo "Build:"
	@echo "  make                  Build receiver and transmitter"
	@echo "  make receiver         Build receiver firmware"
	@echo "  make transmitter      Build transmitter firmware"
	@echo ""
	@echo "Flash:"
	@echo "  make flash-receiver   Flash receiver Arduino"
	@echo "  make flash-transmitter Flash transmitter Arduino"
	@echo ""
	@echo "Ports:"
	@echo "  RECEIVER_PORT=$(RECEIVER_PORT)"
	@echo "  TRANSMITTER_PORT=$(TRANSMITTER_PORT)"
	@echo ""
	@echo "Override ports:"
	@echo "  make flash-receiver RECEIVER_PORT=/dev/ttyACM0"
	@echo "  make flash-transmitter TRANSMITTER_PORT=/dev/ttyACM1"
	@echo ""
	@echo "Other:"
	@echo "  make clean            Remove generated files"

$(OUTPUT):
	mkdir -p $(OUTPUT)

receiver: $(OUTPUT)/receiver.hex

transmitter: $(OUTPUT)/transmitter.hex

$(OUTPUT)/receiver.elf: src/receiver.c | $(OUTPUT)
	$(CC) $(CFLAGS) $< -o $@

$(OUTPUT)/transmitter.elf: src/transmitter.c | $(OUTPUT)
	$(CC) $(CFLAGS) $< -o $@

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

