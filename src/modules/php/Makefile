NAME 		= 	php.so

SRC 		=	php.cpp

OBJ 		= 	$(SRC:.cpp=.o)

CXXFLAGS 	= -W -Wall -fPIC -I ../../../include -std=c++17
LDFLAGS 	= -shared -fPIC

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME) mv

mv:
	mv php.so ../../../sharedModules/

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
