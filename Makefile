LDFLAG = -ltensorflow
TARGET = cts
OBJECTS = main.o


.PHONY: run clean
run: $(TARGET) graph.pb
	./$(TARGET)

graph.pb:
	./generate_graph.py

clean:
	$(RM) $(TARGET) $(OBJECTS) ./graph.pb

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAG)
main.o: main.c
