# Name
NAME=base

# Dirs
ROOT=./src
LLIBDIR=./lib
GLIBDIR=/usr/local/lib
SO=lib$(NAME).so
A=lib$(NAME).a
LIBA=$(LLIBDIR)/$(A)
LIBSO=$(LLIBDIR)/$(SO)

# Files
CODEDIRS=$(shell find $(ROOT) -type d)
INCDIRS=./include
INCFILES=$(foreach D, $(INCDIRS),$(wildcard $(D)/*.h))

# Compiler
CC=gcc

# Flags
OPT=-O0
DEPFLAGS=-lm
WARNFLAGS=-Wall -Wextra
ERRORFLAGS=-Werror
DEBUGFLAGS=-g -v
LIBFLAGS=-fPIC
CFLAGS=$(foreach D,$(INCDIRS),-I$(D)) $(DEPFLAGS)
LINKFLAGS= $(foreach D,$(INCDIRS),-L$(D)) $(DEPFLAGS)

# for-style iteration (foreach) and regular expression completions (wildcard)
CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.c))

# regular expression replacement
OBJECTS=$(patsubst %.c,%.o,$(CFILES))
DEPFILES=$(patsubst %.c,%.d,$(CFILES))

install: $(LIBSO) $(LIBA)
$(LIBSO): $(OBJECTS)
	mkdir -p $(LLIBDIR)
	$(CC) -shared -o $@ $^ $(LINKFLAGS)
	$(foreach D,$(INCFILES),$(shell ln -sf $(shell pwd)/$(D) /usr/local/$(D)))
	ln -sf $(shell pwd)/$(LIBSO) $(GLIBDIR)/$(SO)
	touch /etc/ld.so.conf.d/local_dynamic_lib.conf /etc/ld.so.conf.d/local_dynamic_include.conf
	echo "/usr/local/lib" > /etc/ld.so.conf.d/local_dynamic_lib.conf
	echo "/usr/local/include" > /etc/ld.so.conf.d/local_dynamic_include.conf
	ldconfig

$(LIBA): $(OBJECTS)
	ar -r $@ $^

# only want the .c file dependency here, thus $< instead of $^.
%.o:%.c
	$(CC) $(LIBFLAGS) $(CFLAGS) -c -o $@ $<

uninstall:
	$(foreach D,$(INCFILES),$(shell rm /usr/local/$(D)))
	rm $(GLIBDIR)/$(SO)
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES) $(LIBA) $(LIBSO) $(DYNAMICLIB)

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
