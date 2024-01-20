all:
	@gcc -o fm window_creation.c set_menu.c window_destruction.c menu_destruction.c render.c print_title.c menu_display.c main.c -lpanel -lmenu -lncurses -g
