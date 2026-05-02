SRC := s21_base.c s21_big_decimal.c s21_convert.c s21_arithmetic.c s21_compare.c s21_another.c s21_output.c s21_extra.c
TEST_SRC := s21_test_all.c

OBJ := $(SRC:.c=.o)
TEST_OBJ := $(TEST_SRC:.c=.o)

# -Werror
CFLAGS := -Wall -Wextra -Werror -std=c11
GCOV_FLAGS := -fprofile-arcs -ftest-coverage

ifeq ($(shell uname), Darwin)
  # mac
  TEST_FLAGS = -lcheck -lm -lpthread
  OPEN = open
else
  # linux
  TEST_FLAGS = -lcheck -lrt -lm -lsubunit
  # --new-window-
  OPEN = x-www-browser
endif

all: s21_decimal.a

s21_decimal.a: $(OBJ)
	ar rcs s21_decimal.a $(OBJ)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

test: $(TEST_OBJ) $(OBJ)
ifeq ($(shell uname), Darwin)
	$(CC) $(FLAGS) $(TEST_FLAGS) $(TEST_OBJ) $(OBJ) -o test
else
	$(CC) $(FLAGS) -pthread -o test $(TEST_OBJ) $(OBJ) $(TEST_FLAGS)
endif
	valgrind --tool=memcheck --leak-check=yes ./test

gcov_report:
	$(CC) --coverage $(TEST_SRC) $(SRC) $(TEST_FLAGS) $(GCOV_FLAGS) -o test
	./test
	lcov --directory . --capture -o coverage.info
	genhtml --output-directory report --legend coverage.info
	$(OPEN) report/index.html

clean:
	rm -rf *.out *.o *.a *.info *.gcda *.gcno run test report

