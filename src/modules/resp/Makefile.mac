NAME 		= 	resp.so

SRC 		=	RespModule.cpp \
				../../services/HeaderManager.cpp

OBJ 		= 	$(SRC:.cpp=.o)

CXXFLAGS 	= -g3 -W -Wall -fPIC -I ../../../include -I ../../services -std=c++17 -dynamiclib -flat_namespace

LDFLAGS 	= -shared -fPIC -L/usr/local/opt/openssl/lib #-L/usr/local/ssl/lib
LDLIBS		= -lssl -lcrypto

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)

all: $(NAME) mv

mv:
	mv resp.so ../../../sharedModules/

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
