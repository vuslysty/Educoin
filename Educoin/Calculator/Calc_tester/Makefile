ifndef GTEST_DIR
GTEST_DIR = ./googletest/googletest
endif

CPPFLAGS += -isystem $(GTEST_DIR)/include

CXXFLAGS += -g -std=c++11 -Wall -Wextra

TESTS = gTests

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

all : $(TESTS)

clean :
	rm -fr $(TESTS) gtest.a gtest_main.a *.o

gtest-all.o : $(GTEST_SRCS_)
	clang++ $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	clang++ $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

gTests.o: gTests.cpp gTests.hpp $(GTEST_HEADERS)
	clang++ -c gTests.cpp -o gTests.o $(CXXFLAGS) $(CPPFLAGS)

$(TESTS): gTests.o gtest_main.a
	clang++ $^ -o $@ -L. -lboost_iostreams -lboost_filesystem -pthread

targ_googletest: googletest
	git clone https://github.com/google/googletest