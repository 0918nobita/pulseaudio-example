main: main.c
	gcc main.c -o main -lpulse-simple -lpulse -lm

.PHONY: clean
clean:
	rm main
