

/* NOTE that if CONFIG_FEATURE_USE_INITTAB is NOT defined,
    * then parse_inittab() simply adds in some default
    * actions(i.e., runs INIT_SCRIPT and then starts a pair
    * of "askfirst" shells). If CONFIG_FEATURE_USE_INITTAB
    * _is_ defined, but /etc/inittab is missing, this
    * results in the same set of default behaviors.
    */
static void parse_inittab(void)
{
#if ENABLE_FEATURE_USE_INITTAB
    char *token[4];
    parser_t *parser = config_open2("/etc/inittab", fopen_for_read);

    if (parser == NULL)
#endif
    {
        /* No inittab file - set up some default behavior */
        /* Reboot on Ctrl-Alt-Del */
        new_init_action(CTRLALTDEL, "reboot", "");
        /* Umount all filesystems on halt/reboot */
        new_init_action(SHUTDOWN, "umount -a -r", "");
        /* Swapoff on halt/reboot */
        if (ENABLE_SWAPONOFF)
            new_init_action(SHUTDOWN, "swapoff -a", "");
        /* Prepare to restart init when a QUIT is received */
        new_init_action(RESTART, "init", "");
        /* Askfirst shell on tty1-4 */
        new_init_action(ASKFIRST, bb_default_login_shell, "");
//TODO: VC_1 instead of ""? "" is console -> ctty problems -> angry users
        new_init_action(ASKFIRST, bb_default_login_shell, VC_2);
        new_init_action(ASKFIRST, bb_default_login_shell, VC_3);
        new_init_action(ASKFIRST, bb_default_login_shell, VC_4);
        /* sysinit */
        new_init_action(SYSINIT, INIT_SCRIPT, "");
        return;
    }

#if ENABLE_FEATURE_USE_INITTAB
    /* optional_tty:ignored_runlevel:action:command
        * Delims are not to be collapsed and need exactly 4 tokens
        */
    while (config_read(parser, token, 4, 0, "#:",
                PARSE_NORMAL & ~(PARSE_TRIM | PARSE_COLLAPSE))) {
        /* order must correspond to SYSINIT..RESTART constants */
        static const char actions[] ALIGN1 =
            "sysinit\0""wait\0""once\0""respawn\0""askfirst\0"
            "ctrlaltdel\0""shutdown\0""restart\0";
        int action;
        char *tty = token[0];

        if (!token[3]) /* less than 4 tokens */
            goto bad_entry;
        action = index_in_strings(actions, token[2]);
        if (action < 0 || !token[3][0]) /* token[3]: command */
            goto bad_entry;
        /* turn .*TTY -> /dev/TTY */
        if (tty[0]) {
            if (strncmp(tty, "/dev/", 5) == 0)
                tty += 5;
            tty = concat_path_file("/dev/", tty);
        }
        new_init_action(1 << action, token[3], tty);
        if (tty[0])
            free(tty);
        continue;
    bad_entry:
        message(L_LOG | L_CONSOLE, "Bad inittab entry at line %d",
                parser->lineno);
    }
    config_close(parser);
#endif
}

