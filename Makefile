CC = gcc
CFLAGS = -c -Wall
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage

ifeq ($(OS),Darwin)
	TST_LIBS = -lcheck
else
	TST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit
endif

COV_LIBS = -coverage
SRC_DIR= src
TST_DIR= tests
SRC_FILES = $(addprefix $(SRC_DIR)/, *.c) 
TST_FILES = $(addprefix $(TST_DIR)/, *.c)
GCOV = gcovr 
GCONV_FLAGS = -r . --html --html-details -e "tests/"


all: coverage_report.html

linkedlist.o:  $(SRC_FILES) $(addprefix $(SRC_DIR)/, linkedlist.h)
	$(CC) $(CFLAGS) $(PROFILE_FLAGS) $(SRC_FILES) 

check_linkedlist.o: $(TST_FILES)
	$(CC) $(CFLAGS) $(PROFILE_FLAGS)  $(TST_FILES) 

check_linkedlist_test: linkedlist.o check_linkedlist.o
	$(CC) linkedlist.o check_linkedlist.o $(TST_LIBS) $(COV_LIBS) -o check_linkedlist_test

test: check_linkedlist_test
	./check_linkedlist_test

coverage_report.html: test
	$(GCOV) $(GCONV_FLAGS) -o coverage_report.html

.PHONY: clean all

clean:
	-rm *.o *.html *.gcda *.gcno check_linkedlist_test
