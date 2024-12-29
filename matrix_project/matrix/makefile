CC = gcc
CFLAGS = -std=c23 \
  -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings \
  -O0 -g3 \
  -DWANT_MAT_EXT
objects = main.o matrix_LDS.o
executable = main
makefile_indicator = .\#makefile\#

.PHONY: all clean

all: $(executable)

clean:
	$(RM) $(objects) $(executable)
	@$(RM) $(makefile_indicator)

$(executable): $(objects)
	$(CC) $(objects) -o $(executable)

main.o: main.c matrix_LDS.h
matrix_LDSC.o: matrix_LDS.c matrix_LDS.h
include $(makefile_indicator)

$(makefile_indicator): makefile
	@touch $@
	@$(RM) $(objects) $(executable)
