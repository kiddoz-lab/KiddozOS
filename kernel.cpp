#define MULTIBOOT_MAGIC 0x1BADB002
#define MULTIBOOT_FLAGS 0x00
#define MULTIBOOT_CHECKSUM (unsigned int)-(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

__attribute__((section(".multiboot")))
const struct {
    unsigned int magic;
    unsigned int flags;
    unsigned int checksum;
} multiboot_header = {
    MULTIBOOT_MAGIC,
    MULTIBOOT_FLAGS,
    MULTIBOOT_CHECKSUM
};

// Your red text logic goes here...
void kernel_main() {
    char* video_memory = (char*)0xb8000;
    const char* msg = "KiddoZ OS: Terminal Husk Active";
    for(int i = 0; msg[i] != '\0'; i++) {
        video_memory[i*2] = msg[i];
        video_memory[i*2+1] = 0x04; // Red color
    }
    while(1);
}
