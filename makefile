CC        :=  g++
NAME      :=  libataxx
SRCDIR    :=  src
OBJDIR    :=  obj
BINDIR    :=  build

SRC       :=  $(wildcard $(SRCDIR)/*.cpp)

SNAME     :=  $(NAME).a
SDIR      :=  $(BINDIR)/static
SOBJ      :=  $(SRC:src/%.cpp=$(SDIR)/%.o)

DNAME     :=  $(NAME).so
DDIR      :=  $(BINDIR)/shared
DOBJ      :=  $(SRC:src/%.cpp=$(DDIR)/%.o)

CXXFLAGS  :=  -Wall -Wextra -Wshadow
CXXRFLAGS :=  -O2 -DNDEBUG
LDFLAGS   :=  -L.
ARFLAGS   :=  crf

.PHONY: all clean fclean re static dynamic

all: static dynamic

static: $(SNAME)

dynamic: $(DNAME)

$(SNAME): $(SOBJ)
	$(AR) $(ARFLAGS) $(BINDIR)/static/$@ $^

$(DNAME): CXXFLAGS += -fPIC
$(DNAME): LDFLAGS += -shared

$(DNAME): $(DOBJ)
	$(CC) $(LDFLAGS) $^ -o $(BINDIR)/shared/$@

$(SDIR)/%.o: src/%.cpp | $(SDIR)
	$(CC) $(CXXFLAGS) $(CXXRFLAGS) -o $@ -c $<

$(DDIR)/%.o: src/%.cpp | $(DDIR)
	$(CC) $(CXXFLAGS) $(CXXRFLAGS) -o $@ -c $<

$(SDIR) $(DDIR):
	@mkdir $@

clean:
	$(RM) -r $(SDIR) $(DDIR)

fclean: clean
	$(RM) $(SNAME) $(DNAME)

re: fclean all
