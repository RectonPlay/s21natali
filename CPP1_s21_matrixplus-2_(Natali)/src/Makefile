CC=g++
LC = lcov
CFLAGS = -Wall -Wextra -Werror
AFLAGS = ar rc
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LCOVFLAGS = -c -d . -o
LIBSOURCES = $(wildcard matrix_*.cc)
TESTSOURSES =  test.cc
SOURCES = $(TESTSOURSES) $(LIBSOURCES)
LIBOBJECTS = $(patsubst %.cc, %.o, $(LIBSOURCES))
OBJECTS = $(patsubst %.cc, %.o, $(SOURCES))
EXECUTABLE = test
OFLAGS = -lgtest -lgtest_main -pthread -o
PROJECT_NAME = s21_matrix_oop
ifeq ($(shell uname -s),Linux)
OPEN_CMD = xdg-open
endif
ifeq ($(shell uname -s),Darwin) # MacOS
OPEN_CMD = open
endif
all:  s21_matrix_oop.a 

%.o: %.cc
	$(CC) -c $< -o $@

test: $(OBJECTS)
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(OBJECTS) $(OFLAGS) $@
	./test

retest: clean test

s21_matrix_oop.a:$(OBJECTS)
	ar rcs $@ $^

gcov_report: test
	$(LC) $(LCOVFLAGS) report.info
	genhtml report.info
	$(OPEN_CMD) ./index.html

check:
	clang-format --style=Google -n $(SOURCES) *.h

clean:
	@-rm -rf src */*.o  *.png *.o 
	@-rm -rf *.gcno *.gcda *.gch *.info *.html *.a *.css
	@-rm -rf */*.gcno */*.gcda */*.gch */*.info */*.html */*.a */*.css
	@-rm ./test
	@-rm -rf ./usr
	@echo clear
rebuild: clean all
