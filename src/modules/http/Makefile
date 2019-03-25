NAME 		= 	http.so

SRC 		=	HttpModule.cpp

OBJ 		= 	$(SRC:.cpp=.o)

CXXFLAGS 	= -W -g3 -Wall -fPIC -I ../../../include -std=c++17 -dynamiclib -flat_namespace

LDFLAGS 	= -shared -fPIC -L/usr/local/opt/openssl/lib #-L/usr/local/ssl/lib
LDLIBS		= -lssl -lcrypto

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)

all: $(NAME) mv

mv:
	mv http.so ../../../sharedModules/

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
