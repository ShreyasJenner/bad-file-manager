ncurses library to display file manager
used by file-manager

### Working
- endwin isn't called ==> resolves flickering issues
- color attributes added to diff b/w files and dirs
- first character of argc is expected to be either 'D' or 'F' ==> used to diff b/w colors

### To-do:
- [x] add color support for directories
- [x] re-render when resizing terminal
- [ ] search support
