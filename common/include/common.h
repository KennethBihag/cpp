#ifndef COMMON_H
#define COMMON_H

#define API_DECL

#ifdef SHARED_LIB
	#ifdef EXPORT_LIB
		#define API_DECL __declspec(dllexport)
	#else
		#define API_DECL __declspec(dllimport)
	#endif
extern "C" {
#endif

API_DECL void libfunc(void);
API_DECL int encrypt_char(char ch,int key);
API_DECL const char* load_file_to_buffer(const char *filename);
API_DECL const char* get_file_ext(const char *filename);

#ifdef SHARED_LIB
}
#endif


#endif