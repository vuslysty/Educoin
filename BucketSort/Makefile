NAME = bucketSorter

TESTER_DIR = ./Tester

COMPILER = clang++-6.0			

LINK_FLAGS = -fsanitize=address,undefined
BUILD_FLAGS = -std=c++11 -Wall -Wextra -Werror -pedantic -g

SRCS =  main.cpp

OBJS = $(SRCS:.cpp=.o)

INC =	BucketSort.hpp

.PHONY : all
all: cppcheck clang-tidy $(NAME)
	make -C $(TESTER_DIR)

.PHONY : googletest
googletest: 
	@if [ ! -d $(TESTER_DIR)/googletest ]; then \
		git clone https://github.com/google/googletest $(TESTER_DIR)/googletest ; \
	fi

.PHONY : cppcheck
cppcheck:
	cppcheck --error-exitcode=1 --std=c++11 --language=c++ $(SRCS) $(INC) 

.PHONY : clang-tidy
clang-tidy:
	clang-tidy main.cpp --

.PHONY : clang-format
clang-format:
	clang-format --style=file -i $(SRCS) $(INC)


$(NAME) : $(OBJS)
	$(COMPILER) -o $(NAME) $(OBJS) $(LINK_FLAGS)

%.o: %.cpp $(INC)
	$(COMPILER) -o $@ -c $< $(BUILD_FLAGS)

.PHONY : clean
clean:
	rm -f $(OBJS)
	make clean -C $(TESTER_DIR)

.PHONY : fclean
fclean: clean
	rm -f $(NAME)
	make fclean -C $(TESTER_DIR)

.PHONY : re
re: fclean all