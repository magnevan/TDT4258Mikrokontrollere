

CC=arm-cortexm3-uclinuxeabi-gcc
CFLAGS+= -c#-O2 -g -Wall #this does not take headerfiles
LDFLAGS+=-ln
SOURCES= chess.c chess_game.c chess_player.c chess_cell.c chess_board.c chess_piece.c  chess_rules.c chess_piece_pawn.c chess_piece_king.c chess_piece_queen.c chess_piece_diagonal.c chess_piece_straight.c chess_piece_knight.c chess_view_terminal.c chess_view.c screen.c
OBJECTS=$(SOURCES:.c=.o)
HEADERS= chess_game.h chess_piece.h chess_view_terminal.h chess_rules.h chess_board.h chess_cell.h piece_types.h player_types.h color_types.h screen.h
EXECUTABLE=game

all: $(HEADERS) $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@




install:

clean :
	-rm -rf *.o *.gdb game
.PHONY : all install clean
