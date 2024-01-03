SOURCES=$(shell find ./src -name "*.cpp")
OBJECTS := $(addprefix build/,$(SOURCES:%.cpp=%.o))
TARGET=build/main

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LINK.cpp) $^ $(LOADLIBES) $(LDLIBS) -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS)