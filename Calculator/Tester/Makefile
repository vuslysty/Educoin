TESTS = gTests

GTEST_DIR = ./googletest/googletest

LINK_FLAGS =  -lboost_iostreams -lboost_filesystem -lpthread -lboost_system
LINK_FLAGS += -fsanitize=address,undefined

COMPILER = clang++-6.0


CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -std=c++11 -Wall -Wextra -pedantic -Werror

GTEST_HEADERS =  $(GTEST_DIR)/include/gtest/*.h
GTEST_HEADERS += $(GTEST_DIR)/include/gtest/internal/*.h

SRCS =	gTests.cpp

INC =	gTests.hpp

all : cppcheck $(TESTS)
	./$(TESTS)

clean :
	rm -fr gtest.a gtest_main.a *.o

fclean : clean
	rm -fr $(TESTS)

gtest-all.o : $(GTEST_SRCS_)
	$(COMPILER) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(COMPILER) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

gTests.o: gTests.cpp gTests.hpp $(GTEST_HEADERS)
	$(COMPILER) -c gTests.cpp -o gTests.o $(CXXFLAGS) $(CPPFLAGS)

$(TESTS): gTests.o gtest_main.a
	$(COMPILER) $^ -o $@ $(LINK_FLAGS)

.PHONY : cppcheck
cppcheck:
	cppcheck --error-exitcode=1 --std=c++11 --language=c++ $(SRCS) $(INC) 

.PHONY : clang-format
clang-format:
	clang-format --style=file -i $(SRCS) $(INC)