SERVER_ADDR = 104.131.145.13

CPP = g++

TARGET = server

SRC_DIR = ./
EXTRAINCDIRS = ./inc
EXTRAINCDIRS += $(MYSQL_INC)

# SRC files
CPPSRC = $(wildcard $(SRC_DIR)src/*.cpp)

CPPOBJ = $(CPPSRC:.cpp=.o)

CFLAGS = $(patsubst %,-I%,$(EXTRAINCDIRS))
CFLAGS += `mysql_config --cflags`
# CFLAGS += -g

LDFLAGS += -lpthread
LDFLAGS += -Wl,-Map=$(TARGET).map
LDFLAGS += `mysql_config --libs`

# Link: create TARGET from object files.
$(TARGET) : $(CPPOBJ)
	$(CPP) $(CPPOBJ) -o $(TARGET) $(LDFLAGS)

# Compile: create object files from C++ source files.
$(CPPOBJ) : %.o : %.cpp
	$(CPP) -c $(CFLAGS) $< -o $@

clean:
	-rm $(TARGET)
	-rm $(CPPOBJ)

upload:
	scp $(TARGET) root@$(SERVER_ADDR):
