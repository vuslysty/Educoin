NAME = mult_matrix

LINK_FLAGS = -pthread
BUILD_FLAGS = -std=c++11

SRCS = mult_matrix.cpp

OBJ = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	@g++ -o $(NAME) $(OBJ) $(LINK_FLAGS)

%.o: %.cpp
	@g++ -o $@ -c $< $(BUILD_FLAGS)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all