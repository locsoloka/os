#ifndef BMP_H_DEFINED
#define BMP_H_DEFINED

void clear_screen(void);
int kprint(char *text, int cursor);
int kprint_ch(char text, int cursor);
int kline_break(int cursor);

#endif