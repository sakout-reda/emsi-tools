CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
AR = ar -rcs
RM = rm -f
CTAGS = ctags
TAGS = .tags

SRC = $(wildcard *.c) $(wildcard transaction/*.c)
OBJ = $(patsubst %.c,%.o,$(SRC))

.PHONY: all clean distclean oclean tags libhblk_blockchain.a

all: libhblk_blockchain.a

clean: oclean
	$(RM) libhblk_crypto.a

distclean: clean
	$(RM) $(TAGS)

oclean:
	$(RM) $(OBJ)

tags:
	$(CTAGS) -f $(TAGS) -R

libhblk_blockchain.a: $(OBJ)
	$(AR) $@ $^
