NAME		=	computor

CPP			=	clang++

FLAGS		=	-std=c++17

VPATH		=	./srcs/
SRCS		=	computor.cpp

HEADERS_DIR	=	./srcs/include/

HEADERS		=	$(addprefix $(HEADERS_DIR), complex.hpp math_a_little.hpp)

INCLUDES		=	-I$(HEADERS_DIR)

OBJ_DIR		=	./obj/

O_FILE			=	$(patsubst %.cpp, $(OBJ_DIR)%.o, $(SRCS))

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ_DIR) $(O_FILE)
	$(CPP) $(O_FILE) -o $(NAME)

$(O_FILE): $(OBJ_DIR)%.o: %.cpp $(HEADERS)
	$(CPP) $(INCLUDES) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR)

PHONY: fclean
fclean: clean
	@rm -f $(NAME)

.PHONY: re
re:		fclean all