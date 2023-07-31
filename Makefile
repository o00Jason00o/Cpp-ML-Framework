all: run
my_program: main.o utility.o
    g++ -o $@ $^

main.o: main.cpp
    g++ -c $<

utility.o: utility.cpp
    g++ -c $<

clean:
    rm -f *.o run