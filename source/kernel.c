void kernel_main(void) {
    // A VGA memória címe, ide írva jelenik meg a szöveg a képernyőn
    volatile char* vga = (volatile char*) 0xB8000;
    const char* msg = "Sikeresen elindult a C kód az OS nelkuli gepen!";
    
    for (int i = 0; msg[i] != '\0'; i++) {
        vga[i * 2] = msg[i];      // Karakter
        vga[i * 2 + 1] = 0x2F;    // Szín (Zöld alapon fehér)
    }
}