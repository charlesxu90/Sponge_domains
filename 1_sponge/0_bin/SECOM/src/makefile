CC		= g++
OBJDIR	= ./../bin
OBJ		= $(patsubst %.cpp, %.o, $(wildcard *.cpp))
TARGET	= $(OBJDIR)/SECOM
.PHONY: all clean

all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)
$(OBJDIR)/%.o: %.cpp
	$(CC) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

clean:
	@rm -f $(TARGET) $(wildcard *.o)
	@rm -rf $(OBJDIR)
