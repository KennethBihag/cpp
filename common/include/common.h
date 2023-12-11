#ifndef COMMON_H
#define COMMON_H

#ifdef STATIC_BUILD
extern "C" {
#endif

void libfunc(void);
int encrypt_char(char ch,int key);
const char* load_file_to_buffer(const char *filename);
const char* get_file_ext(const char *filename);

#ifdef STATIC_BUILD
}
#endif


#endif