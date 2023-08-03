OS := $(shell uname)
CC = -Wall -Werror -Wextra -std=c11
FLAGS = -lcheck -lpthread -fprofile-arcs

ifeq ($(OS),Darwin)
	FLAGS += -ftest-coverage
	OPEN_CMD = open
else
	FLAGS += -lm -lrt -lsubunit -ftest-coverage
	OPEN_CMD = xdg-open
endif

all: clean my_matrix.a test gcov_report

my_matrix.a:
	gcc $(CC) -c my_matrix/my_*.c
	ar -crs my_matrix/my_matrix.a my_*.o

gcov_report: clean
	gcc $(CC) tests/tests.c my_matrix/my_*.c $(FLAGS) -o test
	./test
	lcov -t "./test"  -o report.info --no-external -c -d .
	genhtml -o report report.info
	$(OPEN_CMD) ./report/index.html

	rm -rf *.gcno *gcda *.gco

clean:
	rm -rf *.o my_matrix/*.a test
	rm -rf *.gcno *gcda *.gcov gcov
	rm -rf report report.info

rebuild: clean my_matrix.a test

test: my_matrix.a
	gcc $(CC) tests/tests.c my_matrix/my_matrix.a $(FLAGS) -lgcov -coverage -o test
	./test