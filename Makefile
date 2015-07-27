all:
	gcc -g -o quicksort quicksort.c -lm

clean:
	rm quicksort 
