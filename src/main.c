/*
 * main.c
 * This file is part of Stjerm
 *
 * Copyright (C) 2007 - Stjepan Glavina
 * Copyright (C) 2007 - Markus Groß
 * Copyright (C) 2008, 2009, 2011 Thomas Pifer
 *
 * Stjerm is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Stjerm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Stjerm; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 */

#include <gtk/gtk.h>
#include "stjerm.h"

int sargc;
char **sargv;

extern Option options[OPTION_COUNT]; //Defined in config.c

void print_help(void);
void print_info(void);
void print_version(void);

void print_help(void) {
    printf("Usage: %s [action] [options]\n\n"
           "Actions are:\n"
           "  --help\tPrint this message\n"
           "  --info\tPrint .Xdefaults options and exit\n"
           "  --version\tPrint version information and exit\n"
           "  --toggle\tShow/Hide the current stjerm instance\n"
           "(When using an action command, the options are ignored)\n\n"
           "Options are:\n", sargv[0]);
    /*
     * i is declared outside of the for statement because the current C standard 
     * that GCC uses does not support declaration inside of a loop.
     */
    int i = 0;
    Option o;   //Option is a struct defined in stjerm.h
    for (i = 0; i < OPTION_COUNT; i++) {
        o = options[i];
        printf("  %s %s\t%s\n", o.short_name, o.var_type, o.desc);
    }
    printf("\t\tYou may specify no palette, or a complete one with 16 total colors\n"
           "\t\tFor this you have to use -c0, -c1, ..., -c15.\n\n"
           "Note:     Any colors in hex codes are entered without the leading '#'.\n\n"
           "Examples: %s -fn \"Liberation Mono 11\" -bg white -k F12 -sh /bin/bash\n"
           "          %s -bg black -fg green -w 800 -h 405 -s right -m alt -k f -l 10000\n"
           "          %s -b thick -w 500 -p left -t best -o 90 -m shift -k tab -sh /bin/zsh\n\n"
           "Use --info to get a list of available .Xdefaults options for stjerm.\n\n"
           "Report bugs to zero456@gmail.com.\n"
           "stjerm home page: http://code.google.com/p/stjerm-terminal-emulator/\n"
           "General help using GNU software: http://www.gnu.org/gethelp/\n",
           sargv[0], sargv[0], sargv[0]);
}

void print_info(void) {
    printf("Usage: %s [action] [options]\n\n"
           "Actions are:\n"
           "  --help\tDisplay command line options menu\n"
           "  --info\tDisplay .Xdefault options\n"
           "  --toggle\tShow/Hide the current stjerm instance\n"
           "(When using an action command, the .Xdefaults options are ignored)\n\n"
           "The .Xdefault options are read from ~/.Xdefaults.\n"
           "To specify an option in .Xdefaults use this syntax:\n"
           "stjerm.OPTION: VALUE\n"
           "Example: stjerm.key: f12\n\n"
           "Available .Xdefaults options:\n", sargv[0]);
    int i = 0;
    Option o;
    for (i = 0; i < OPTION_COUNT; i++) {
        o = options[i];
        printf("  %s:  \t%s      \t%s\n", o.long_name, o.var_type, o.desc);
    }
    printf("\t\t\t\tYou may specify no palette, or a complete one with 16 total colors.\n"
           "\t\t\t\tFor this you have to use color0, color1, ..., color15.\n");
}

void print_version(void) {
    printf("Stjerm %s\n"
           "Copyright (C) 2007 Stjepan Glavina\n"
           "Copyright (C) 2007 Markus Gross\n"
           "Copyright (C) 2011 Thomas Pifer\n"
           "License GPLv2+: GNU GPL version 2 or later <http://gnu.org/licenses/gpl.html>\n"
           "This is free software: you are free to change and redistribute it.\n"
           "There is NO WARRANTY, to the extent permitted by law.\n", 
           STJERM_VERSION);
}

int main(int argc, char *argv[]) {
    sargc = argc;
    sargv = argv;

    if (!g_thread_supported())
        g_thread_init(NULL);
    gdk_threads_init();
    gtk_init(&argc, &argv);

    conf_init();
    build_mainwindow();

    gdk_threads_enter();
    gtk_main();
    gdk_threads_leave();

    return 0;
}

