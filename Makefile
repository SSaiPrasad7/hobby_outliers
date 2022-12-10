all: compile

compile:
	gcc outlier.c -o obj

clean:
	rm -f obj