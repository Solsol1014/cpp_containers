.DEFAULT_GOAL	= all

NAME			= containers
CXX				= c++
CXXFLAGS		= -Wall -Wextra -Werror -std=c++98 -ISTL
CPPFLAGS		=
LDFLAGS			=
LDLIBS			=
FILE			= makefiletest
SRCS 			= $(addprefix $(PREFIX), $(addsuffix $(SUFFIX).cpp, $(FILE)))
OBJS 			= $(SRCS:.cpp=.o)
COMMON_SRCS		:= new.cpp
COMMON_OBJS		:= $(COMMON_SRCS:.cpp=.o)

# ********************************* MAKE RULES ******************************* #

all : $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) $(LDLIBS)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

% : %.o $(COMMON_OBJS)
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY : all clean fclean re
