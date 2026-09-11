#ifndef SCREEN_H_DEFINED
#define SCREEN_H_DEFINED

void grapics_init(void);

void clear_screen(void);
void kprint(char *text);
void kprint_ch(char text);
void kline_break(void);
char int_to_char(int number);


void kprint_raw(char *text);
void kprint_ch_raw(char text);


#endif
