# Name
NAME=base

# Dirs
#
ROOT=./src
LLIBDIR=./lib
OBJ=./obj

TEST=./tests

GLIBDIR=/usr/local/lib

LIBA=$(LLIBDIR)/$(A)
LIBSO=$(LLIBDIR)/$(SO)

CODEDIRS=$(shell find $(ROOT) -type d)
INCDIRS=./include

# Files

SO=lib$(NAME).so
A=lib$(NAME).a

INCFILES=$(foreach D, $(INCDIRS),$(wildcard $(D)/*.h))
CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.c))

TESTS=$(wildcard $(TEST)/*.c)
TESTBINS=$(patsubst $(TEST)/%.c, $(TEST)/bin/%, $(TESTS))

# Compiler
CC=gcc

# Flags
OPT=-O0
DEPFLAGS=-lm
WARNFLAGS=-Wall -Wextra
ERRORFLAGS=-Werror
DEBUGFLAGS=-g -v
LIBFLAGS=-fPIC
LINKFLAGS= $(foreach D,$(INCDIRS),-L$(D)) $(DEPFLAGS)

# Release flags
LOCALFLAGS=$(WARNFLAGS)
DEBUG=$(ERRORFLAGS) $(DEBUGFLAGS) $(WARNFLAGS)
PRODUCTION=$(foreach D,$(INCDIRS),-I$(D)) $(DEPFLAGS)
CFLAGS=$(foreach D,$(INCDIRS),-I$(D)) $(DEPFLAGS) $(LOCALFLAGS)

# regular expression replacement
OBJECTS=$(patsubst %.c,%.o,$(CFILES))
DEPFILES=$(patsubst %.c,%.d,$(CFILES))

all: $(LIBA) $(LIBSO)

production: CFLAGS=$(PRODUCTION)
production: clean
production: $(LIBA) $(LIBSO)

debug: CFLAGS=$(DEBUG)
debug: clean
debug: $(LIBA) $(LIBSO)

install: $(LIBSO) $(LIBA) $(INCFILES)
	cp $(INCFILES) /usr/local/include/
	ln -sf $(shell pwd)/$(LIBSO) $(GLIBDIR)/$(SO)
	touch /etc/ld.so.conf.d/local_dynamic_lib.conf /etc/ld.so.conf.d/local_dynamic_include.conf
	echo "/usr/local/lib" > /etc/ld.so.conf.d/local_dynamic_lib.conf
	echo "/usr/local/include" > /etc/ld.so.conf.d/local_dynamic_include.conf
	ldconfig

uninstall:
	$(foreach D,$(INCFILES),$(shell rm /usr/local/$(D)))
	rm $(GLIBDIR)/$(SO)
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES) $(LIBA) $(LIBSO) $(DYNAMICLIB)

$(LIBSO): $(OBJECTS)
		$(CC) -shared -o $@ $^ $(LINKFLAGS)

$(LIBA): $(OBJECTS)
		ar -r $@ $^

%.o: %.c
	$(CC) $(LIBFLAGS) $(CFLAGS) -c -o $@ $<

$(TEST)/bin/%: $(TEST)/%.c $(LLIBDIR)
	$(CC) $(CFLAGS) $< $(OBJECTS) -o $@ -lcriterion

$(LLIBDIR):
	mkdir -p $@

$(TEST)/bin:
	mkdir -p $@

test: $(LIBA) $(TEST)/bin $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test ; done

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES) $(LIBA) $(LIBSO) $(DYNAMICLIB)

# shell commands are a set of keystrokes away
distribute: clean
	tar zcvf dist.tgz *

# @ silences the printing of the command
# $(info ...) prints output
diff:
	$(info The status of the repository, and the volume of per-file changes:)
	@git status
	@git diff --stat

# include the dependencies
-include $(DEPFILES)

# add .PHONY so that the non-targetfile - rules work even if a file with the same name exists.
.PHONY: all clean distribute diff
