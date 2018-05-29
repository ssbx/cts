LDFLAG = -ltensorflow
TARGET = cts
OBJECTS = main.o


.PHONY: run clean
run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAG)
main.o: main.c
