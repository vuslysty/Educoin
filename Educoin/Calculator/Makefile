NAME = calculator

COMPILER = clang++

LINK_FLAGS =
BUILD_FLAGS = -std=c++11 -Wall -Wextra -Werror

SRCS = 	Executor.cpp\
		LexConditions.cpp\
		Lexer.cpp\
		LexFiniteStates.cpp\
		Parser.cpp\
		ParsFiniteStates.cpp\
		main.cpp

OBJS = $(SRCS:.cpp=.o)

INC =	Calculator.hpp\
		Executor.hpp\
		Lexer.hpp\
		Parser.hpp\
		Token.hpp

.PHONY : all
all: $(NAME)

$(NAME) : $(OBJS)
	$(COMPILER) -o $(NAME) $(OBJS) $(LINK_FLAGS)

%.o: %.cpp $(INC)
	$(COMPILER) -o $@ -c $< $(BUILD_FLAGS)

.PHONY : clean
clean:
	rm -f $(OBJS)

.PHONY : fclean
fclean: clean
	rm -f $(NAME)

.PHONY : re
re: fclean all