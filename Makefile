LDFLAG = -ltensorflow
TARGET = cts
OBJECTS = main.o

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) main.o $(LDFLAG)

clean:
	$(RM) $(TARGET) $(OBJECTS)

main.o: main.c
