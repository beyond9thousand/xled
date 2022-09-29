/* compile command: cc -O3 --std=c11 -pedantic -Wall xkb.c -o xkb -lX11 -lXi */

/* Headers and Defines {{{*/
#include <X11/XKBlib.h>

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define HELP_MESSAGE                                                                                    \
    "xkb -[s] ...\n"                                                                                    \
    "\n"                                                                                                \
    "OPTIONS:\n"                                                                                        \
    "    -s         indicators CAPS_LOCK_STATE NUM_LOCK_STATE\n"                                        \
    "    -j         {\"caps\":\"CAPS_LOCK_STATE\",\"num\":\"NUM_LOCK_STATE\"\n"                         \
    "\n"                                                                                                \
    "EXAMPLES:\n"                                                                                       \
    "    -s1        will print the initial value\n"                                                     \
    "    -s0        won't print the initial value / not providing any args will have the same effect\n" \
    "    -j[1|0]    same as -s\n"                                                                       \
    "\n"

#define BEGIN_XOP    _setup();
#define END_XOP      _finish();

#define ON_OR_OFF(S) (S ? "on" : "off")
/*}}}*/

/* Boilerplates {{{*/
typedef enum {
    NO_STATE        = 0,
    CAPS_LOCK_STATE = 1,
    NUM_LOCK_STATE  = 2,
    BOTH_LOCK_STATE = 3,
} ind_state_t;

Display* display = NULL;

void
_setup(void) {
    display = XOpenDisplay(None);
}

void
_finish(void) {
    if (display != NULL) {
        XFlush(display);
        XCloseDisplay(display);
    }
}
/*}}}*/

void
display_ind_state(Bool ind_keys[2], int event_state, Bool json) {
    switch (event_state) {
        case NO_STATE: ind_keys[0] = ind_keys[1] = False; break;
        case CAPS_LOCK_STATE: ind_keys[0] = True; break;
        case NUM_LOCK_STATE: ind_keys[1] = True; break;
        case BOTH_LOCK_STATE: ind_keys[0] = ind_keys[1] = True; break;
    }

    printf(json ? "{\"caps\":\"%s\",\"num\":\"%s\"}\n" : "indicators %s %s\n",
           ON_OR_OFF(ind_keys[0]),
           ON_OR_OFF(ind_keys[1]));
    fflush(stdout);
}

void
start_led_logger(Bool first_blood, Bool json) {
    Bool ind_keys[2] = {False, False};
    if (first_blood) {
        unsigned int start_state;
        XkbGetIndicatorState(display, XkbUseCoreKbd, &start_state);
        display_ind_state(ind_keys, start_state, json);
    }

    XkbSelectEvents(display, XkbUseCoreKbd, XkbIndicatorStateNotifyMask, XkbIndicatorStateNotifyMask);
    XkbIndicatorNotifyEvent event;
    while (True) {
        XNextEvent(display, (XEvent*) &event);
        display_ind_state(ind_keys, event.state, json);
    }
}

/* Main {{{*/
int
main(int argc, char** argv) {
    if (argc == 1) {
        printf("No arguments given.\n");
        printf(HELP_MESSAGE);
        return EXIT_FAILURE;
    }

    BEGIN_XOP

    int option;
    while ((option = getopt(argc, argv, "-:j::s::h")) != -1) {
        switch (option) {
            case 's': start_led_logger(atoi(optarg ? optarg : "0"), False); break;
            case 'j': start_led_logger(atoi(optarg ? optarg : "0"), True); break;
            case 'h': fprintf(stdout, HELP_MESSAGE); break;
            case '?': fprintf(stderr, "Invalid option.\n" HELP_MESSAGE); break;
            default: fprintf(stderr, "Undefined value.\n" HELP_MESSAGE); break;
        }
    }

    END_XOP
    return EXIT_SUCCESS;
}
/*}}}*/

// vim:filetype=c
