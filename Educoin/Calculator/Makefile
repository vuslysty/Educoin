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
all: cppcheck $(NAME)

.PHONY : cppcheck
cppcheck:
	cppcheck --error-exitcode=1 --std=c++11 --language=c++ $(SRCS) $(INC)

.PHONY : clang-tidy
clang-tidy:
	clang-tidy $(SRCS) $(INC)

.PHONY : clang-format
clang-format:
	clang-format --style=file -i $(SRCS) $(INC)


$(NAME) : $(OBJS)
	$(COMPILER) -o $(NAME) $(OBJS) $(LINK_FLAGS)

# Lexer and Parser will compile without -pedantic key.
# Because FSMs in these files look prettier when used with C99 feature.
#########################################
Lexer.o: Lexer.cpp $(INC)
	$(COMPILER) -o $@ -c $< $(BUILD_FLAGS)

Parser.o: Parser.cpp $(INC)
	$(COMPILER) -o $@ -c $< $(BUILD_FLAGS)
##########################################

%.o: %.cpp $(INC)
	$(COMPILER) -o $@ -c $< $(BUILD_FLAGS) -pedantic

.PHONY : clean
clean:
	rm -f $(OBJS)

.PHONY : fclean
fclean: clean
	rm -f $(NAME)

.PHONY : re
re: fclean all