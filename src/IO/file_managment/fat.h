#include <stdint.h>

#pragma pack(push, 1)

typedef struct
{
    uint8_t  jump_code[3];          // Ugró utasítás az OS boot kódra (pl. 0xEB 0x3C 0x90)
    char     oem_name[8];           // Formázó rendszer neve (pl. "MSDOS5.0" vagy "MKFS16  ")
    
    // --- BIOS Parameter Block (BPB) Kezdete ---
    uint16_t bytes_per_sector;      // Szektor mérete bájtban (szinte mindig 512)
    uint8_t  sectors_per_cluster;   // Szektorok száma egy klaszterben (1, 2, 4, 8, stb.)
    uint16_t reserved_sectors;      // Rezervált szektorok (LBA 0-tól a FAT1-ig, min. 1)
    uint8_t  fat_count;             // FAT táblák száma (alapesetben 2)
    uint16_t root_entry_count;      // Bejegyzések max száma a Root Directory-ban (pl. 512)
    uint16_t total_sectors_16;      // Összes szektor (16 bites). Ha 0, akkor a total_sectors_32 használandó
    uint8_t  media_type;            // Média típus (pl. 0xF8 = Merevlemez/Flash)
    uint16_t sectors_per_fat;       // Egy FAT tábla mérete szektorokban
    uint16_t sectors_per_track;     // CHS geometriához (QEMU-nál lényegtelen)
    uint16_t head_count;            // Fejek száma CHS geometriához
    uint32_t hidden_sectors;        // Rejtett szektorok száma a partíció előtt
    uint32_t total_sectors_32;      // Összes szektor (32 bites, ha total_sectors_16 == 0)

    // --- Extended BPB (FAT12 / FAT16 specifikus) ---
    uint8_t  drive_number;          // BIOS meghajtó szám (pl. 0x80 az első HDD)
    uint8_t  reserved1;             // NT / Windows által fenntartott bájt
    uint8_t  boot_signature;        // Kiterjesztett boot aláírás (0x29, ha a köv. 3 mező létezik)
    uint32_t volume_id;             // Lemez sorozatszáma (random generált ID)
    char     volume_label[11];      // Lemezcímke ("NO NAME    " ha nincs megadva)
    char     fs_type[8];            // Fájlrendszer típusa karakteresen ("FAT16   ")
    
    uint8_t  boot_code[448];        // Bootloader kód helye (ha bootolható lemez)
    uint16_t boot_sector_signature;// Boot szektor aláírás (mindig 0xAA55)
} fat16_boot_sector_t;

#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
    char     filename[8];      // Fájlnév (pl. "TEST    ")
    char     ext[3];           // Kiterjesztés (pl. "TXT")
    uint8_t  attributes;       // Attribútumok (0x20 = normál fájl, 0x10 = mappa)
    uint8_t  reserved[10];
    uint16_t time;
    uint16_t date;
    uint16_t first_cluster;    // *** ITT A LÉNYEG: A KEZDŐ KLASZTER ***
    uint32_t file_size;        // Fájl pontos mérete bájtban
} fat16_entry_t;
#pragma pack(pop)

void file_init(void);
void find_LBA(void);
void file_lookup(void);

