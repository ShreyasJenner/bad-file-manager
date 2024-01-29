all:
	@gcc -o fm print_title.c menu_display.c main.c -lpanel -lmenu -lncurses -g
