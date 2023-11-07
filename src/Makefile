.PHONY: all clean

CC=gcc
FLAGS=-Wall -Wextra -Werror
LDFLAGS=$(shell pkg-config --cflags --libs check)

GCOVFLAGS=-fprofile-arcs -ftest-coverage
LIBNAME=s21_matrix

SRCS=$(wildcard s21_*.c)
GCOVNAME=coverage

all: s21_matrix.a

$(LIBNAME).a:
	$(CC) $(FLAGS) -c $(SRCS)
	ar rc $(LIBNAME).a *.o
	ranlib $(LIBNAME).a
	rm *.o

# s21_matrix: clean 
# 	$(CC) $(FLAGS) -g s21_matrix.c
# 	./a.out

debug: clean 
	$(CC) $(FLAGS) -g s21_matrix.c
	
clean:
	-rm -rf matrix gcov_report/ *.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg *.txt gcov_main test
	
test: clean
	$(CC) $(LDFLAGS) $(SRCS) tests.c -o test
	./test

gcov_report: add_coverage_flag
	$(CC) $(LDFLAGS) $(GCOVFLAGS) $(SRCS) tests.c -o gcov_main
	./gcov_main
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report
	open gcov_report/index.html
	

style_check:
	clang-format --style=Google -n $(SRCS) *.c *.h
	
style:
	clang-format --style=Google -i $(SRCS) *.c *.h

add_coverage_flag:
	$(eval FLAGS += --coverage)
