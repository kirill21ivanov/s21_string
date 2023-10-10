CC = -Wall -Werror -Wextra -std=c11
OS := $(shell uname)
SRC = s21_float.c s21_int.c s21_parsers.c s21_sprintf.c s21_uint.c s21_string_and_char.c s21_exponent.c s21_pointer.c s21_sscanf.c
OBJ = s21_float.o s21_int.o s21_parsers.o s21_sprintf.o s21_uint.o s21_string_and_char.o s21_exponent.o s21_pointer.o s21_sscanf.o

ifeq ($(OS),Linux)
FLAGS = -lcheck -lm -lpthread -lrt -lsubunit
else
FLAGS = -lcheck -lm -lpthread 
endif
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage
COV_LIBS = -lgcov -coverage

all: clean s21_string.a


test: 
	gcc test_dopfunk.c s21_string.a $(FLAGS) $(COV_LIBS) -o test_dopfunk
	./test_dopfunk
	gcc  test_funk.c s21_string.a $(FLAGS) $(COV_LIBS) -o test_funk
	./test_funk
	gcc  test_sprintf.c s21_string.a $(FLAGS) $(COV_LIBS) -o test_sprintf
	./test_sprintf
	gcc  test_sscanf.c s21_string.a $(FLAGS) $(COV_LIBS) -o test_sscanf
	./test_sscanf
	


s21_string.a: s21_string.o s21_sprintf.o s21_dopfunk.o
	ar -crs s21_string.a s21_string.o s21_dopfunk.o ${OBJ}

s21_string.o:
	gcc $(CC) -c s21_string.c

s21_sprintf.o:
	gcc $(CC) -c  ${SRC}

s21_dopfunk.o:
	gcc $(CC) -c s21_dopfunk.c

s21_string_peer:
	gcc $(CC) $(PROFILE_FLAGS) -c s21_dopfunk.c
	gcc $(CC) $(PROFILE_FLAGS) -c  ${SRC}
	gcc $(CC) $(PROFILE_FLAGS) -c s21_string.c
	ar -crs s21_string.a s21_string.o s21_dopfunk.o ${OBJ}

gcov_report:
	lcov -t "gcov_report"  -o report.info --no-external -c -d .
	genhtml -o ./report report.info
	open ./report/index.html

	rm -rf *.gcno *gcda *.gco


clean:
	rm -rf *.o *.a *.out test_funk test_dopfunk test_sprintf test_sscanf
	rm -rf *.gcno *gcda *.gcov gcov
	rm -rf report report.info
	rm -rf .clang-format


style:
	cp ../materials/linters/.clang-format .
	clang-format -i *.c *.h

style_test:
	clang-format -n -style=google *.c *.h

style_1:
	clang-format -i -style=google *.c *.h

