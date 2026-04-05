extern "C" {
    void print_string(const char* str);
    void clear_screen();
    char get_input_char();

    void ksh_start(unsigned int mod_start, unsigned int mod_end) {
        char cmd[64];
        int idx = 0;

        clear_screen();
        
        if (mod_start == 0) {
            print_string("Warning: No External List found in ISO.\n");
        } else {
            print_string("KSH terminal prompt\n");
        }
        
        print_string("Type 'help' for commands.\n\n");

        while (1) {
            print_string("root~ $ ");
            idx = 0;
            
            while (1) {
                char c = get_input_char();
                
                if (c == '\n') {
                    cmd[idx] = '\0';
                    print_string("\n");
                    break;
                } else if (c == '\b') {
                    if (idx > 0) {
                        idx--;
                        print_string("\b");
                    }
                } else if (idx < 63) {
                    cmd[idx++] = c;
                    char out[2] = {c, '\0'};
                    print_string(out);
                }
            }

            if (cmd[0] == 'c' && cmd[1] == 'l' && cmd[2] == 'e' && cmd[3] == 'a' && cmd[4] == 'r' && cmd[5] == '\0') {
                clear_screen();
            } else if (cmd[0] == 'l' && cmd[1] == 's' && cmd[2] == '\0') {
                if (mod_start != 0) {
                    char* fs_ptr = (char*)mod_start;
                    print_string(fs_ptr);
                    print_string("\n");
                } else {
                    print_string("Empty List.\n");
                }
            } else if (cmd[0] == 'c' && cmd[1] == 'l' && cmd[2] == ' ') {
                print_string("Shifting focus to: ");
                print_string(&cmd[3]);
                print_string("\n");
            } else if (cmd[0] == '~' && cmd[1] == ' ') {
                print_string("Opening module stream: ");
                print_string(&cmd[2]);
                print_string("\n[READING FROM MEMORY...]\n");
            } else if (cmd[0] == 'h' && cmd[1] == 'e' && cmd[2] == 'l' && cmd[3] == 'p' && cmd[4] == '\0') {
                print_string("KSH COMMANDS:\n");
                print_string("ls    - List content of list\n");
                print_string("cl    - Change current List context\n");
                print_string("clear - Refresh display\n");
                print_string("~     - Opens a file \n");
            } else if (idx > 0) {
                print_string("Error: Command not recognized.\n");
            }
        }
    }
}