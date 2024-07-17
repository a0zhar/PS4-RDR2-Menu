CC       := gcc
AS       := gcc
OBJCOPY  := objcopy
ODIR     := build
SDIR     := source
IDIR     := include
CFLAGS   := -I$(IDIR) -Llib -O3 -s -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-builtin -nostartfiles -nostdlib -masm=intel -march=btver2 -mtune=btver2 -m64 -mabi=sysv -mcmodel=small -fpie -fpermissive
LFLAGS   := -Xlinker -T linker.x -Wl,--build-id=none
SFLAGS   := -nostartfiles -nostdlib -masm=intel -march=btver2 -mtune=btver2 -m64 -mabi=sysv -mcmodel=large

# Recursively find all .cpp and .s files in the source directory
CFILES   := $(shell find $(SDIR) -type f -name '*.cpp')
SFILES   := $(shell find $(SDIR) -type f -name '*.s')

# Create object file names with the build directory but without the source directory structure
COBJS    := $(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(CFILES))
SOBJS    := $(patsubst $(SDIR)/%.s, $(ODIR)/%.o, $(SFILES))
OBJS     := $(COBJS) $(SOBJS)

TARGET   := $(shell basename $(CURDIR)).bin

# Print informative messages
INFO     := @echo "[$(TARGET)]"

$(TARGET): $(ODIR) $(OBJS)
	@echo "Linking objects into $@"
	@gcc crt0.s $(OBJS) -o temp.t $(CFLAGS) $(LFLAGS)
	@$(OBJCOPY) -O binary temp.t $(TARGET)
	@rm -f temp.t

# Rule to compile .cpp files
$(ODIR)/%.o: $(SDIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $< to $@"
	@gcc -c -o $@ $< $(CFLAGS)

# Rule to assemble .s files
$(ODIR)/%.o: $(SDIR)/%.s
	@mkdir -p $(dir $@)
	@echo "Assembling $< to $@"
	@gcc -c -o $@ $< $(SFLAGS)

$(ODIR):
	@echo "Creating directory $@"
	@mkdir -p $@

.PHONY: clean

clean:
	@echo "Cleaning up"
	@rm -f $(TARGET) $(ODIR)/*.o
	@find $(ODIR) -type d -empty -delete
