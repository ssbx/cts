LDFLAG = -ltensorflow
TARGET = cts
OBJECTS = main.o


.PHONY: run clean
run: data/mnist/train_images.data
run: data/mnist/train_labels.data
run: data/mnist/test_images.data
run: data/mnist/test_labels.data

data/mnist/test_images.data: data/mnist/t10k-images-idx3-ubyte.gz
	 gzip -d -c data/mnist/t10k-images-idx3-ubyte.gz > data/mnist/test_images.data
data/mnist/test_labels.data: data/mnist/t10k-labels-idx1-ubyte.gz
	 gzip -d -c data/mnist/t10k-labels-idx1-ubyte.gz > data/mnist/test_labels.data
data/mnist/train_images.data: data/mnist/train-images-idx3-ubyte.gz
	gzip -d -c data/mnist/train-images-idx3-ubyte.gz > data/mnist/train_images.data
data/mnist/train_labels.data: data/mnist/train-labels-idx1-ubyte.gz
	gzip -d -c data/mnist/train-labels-idx1-ubyte.gz > data/mnist/train_labels.data

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(TARGET) $(OBJECTS) data/mnist/*data

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) main.o $(LDFLAG)
main.o: main.c
