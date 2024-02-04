all:
	@gcc -o fm main_loop.c free_memory.c dynamic_file_indicator.c menu_opts_set.c store_item_values.c print_title.c menu_display.c main.c -lform -lmenu -lncurses
