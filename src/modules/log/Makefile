NAME 		= 	log.so

SRC 		=	log.cpp

OBJ 		= 	$(SRC:.cpp=.o)

CXXFLAGS 	= -W -Wall -fPIC -I ../../../include -std=c++17 -dynamiclib -flat_namespace
LDFLAGS 	= -shared -fPIC

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME) mv

mv:
	mv log.so ../../../sharedModules/

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
