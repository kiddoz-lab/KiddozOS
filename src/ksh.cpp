extern "C" {
    void print_string(const char* str);
    void clear_screen();
    char get_input_char();

    void ksh_start(unsigned int mod_start, unsigned int mod_end) {
        char cmd[64];
        int idx = 0;

        clear_screen();
        
        if (mod_start != 0) {
            print_string("KSH Terminal - prompt module loaded.\n");
        } else {
            print_string("Warning: No External Module found.\n");
        }
        
        print_string("Type 'help' for commands.\n\n");

        while (1) {
            print_string("root~ $ ");
            idx = 0;
            
            while (1) {
                char c = get_input_char();
                if (c == 0) continue;
                
                if (c == '\n') {
                    cmd[idx] = '\0';
                    print_string("\n");
                    break;
                } else if (c == '\b') {
                    if (idx > 0) {
                        idx--;
                        print_string("\b");
                    }
                } else {
                    if (idx < 63) {
                        cmd[idx++] = c;
                        char out[2] = {c, '\0'};
                        print_string(out);
                    }
                }
            }

            if (cmd[0] == 'l' && cmd[1] == 's' && cmd[2] == '\0') {
                if (mod_start != 0) {
                    print_string("[L] bin\n[L] sys\nkernel.bin\n");
                    print_string((char*)mod_start);
                    print_string("\n");
                } else {
                    print_string("Empty List.\n");
                }
            } else if (cmd[0] == 'c' && cmd[1] == 'l' && cmd[2] == ' ') {
                print_string("Shifting focus to List: ");
                print_string(&cmd[3]);
                print_string("\n");
            } else if (cmd[0] == '~' && cmd[1] == ' ') {
                print_string("Opening file stream: ");
                print_string(&cmd[2]);
                print_string("\n---\n");
                if (mod_start != 0) {
                    print_string((char*)mod_start);
                } else {
                    print_string("No data in module.");
                }
                print_string("\n---\n");
            } else if (cmd[0] == 'c' && cmd[1] == 'l' && cmd[2] == 'e' && cmd[3] == 'a' && cmd[4] == 'r') {
                clear_screen();
            } else if (cmd[0] == 'h' && cmd[1] == 'e' && cmd[2] == 'l' && cmd[3] == 'p') {
                print_string("KSH COMMANDS:\n");
                print_string("ls    - View current List\n");
                print_string("cl    - Change to a different List\n");
                print_string("clear - Wipe the screen\n");
                print_string("~     - Open file data\n");
            } else if (idx > 0) {
                print_string("Error: Command '");
                print_string(cmd);
                print_string("' not found.\n");
            }
        }
    }
}