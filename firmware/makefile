CC = sdcc
CFLAGS = -mstm8
LDFLAGS = -mstm8

SOURCE = ./source
BUILD = ./build
OUTPUT = $(BUILD)/output.hex

SOURCES = $(wildcard $(SOURCE)/*.c)
OBJECTS = $(patsubst $(SOURCE)/%.c, $(BUILD)/%.rel, $(SOURCES))

.PHONY: flash clean

$(OUTPUT): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(OUTPUT)

$(BUILD)/%.rel: $(SOURCE)/%.c
	$(CC) $(CFLAGS) -c $< -o $(BUILD)/

flash: $(OUTPUT)
	"C:\Program Files (x86)\STMicroelectronics\st_toolset\stvp\STVP_CmdLine.exe" -BoardName=ST-LINK -Port=USB -ProgMode=SWIM -Device=STM8S103F3 -FileProg="$(OUTPUT)" -no_loop -no_log

clean:
	del /Q "$(BUILD)"