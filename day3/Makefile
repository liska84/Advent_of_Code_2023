NAME = day3

SRC = main.cpp Engine.cpp

OBJ_DIR = obj/
OBJ = $(SRC:.cpp=.o)
OBJ_PREF = $(addprefix $(OBJ_DIR), $(OBJ))

CXX = c++
CXXFLAGS =  -std=c++11
#-Wall -Wextra -Werror
all: $(NAME)

$(NAME): $(OBJ_PREF)
	$(CXX) $(CXXFLAGS) $^ -o $(NAME)

$(OBJ_DIR)%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR)*.o $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all