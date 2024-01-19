all:
	@gcc -o fm menu_item_traversal.c print_title.c menu_display.c main.c -lpanel -lmenu -lncurses -g
