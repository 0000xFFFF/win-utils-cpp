#include <stdio.h>
#include <stdarg.h>

static FILE* tee_file = NULL;
FILE* tee_init(const char* file) {
	tee_file = fopen(file, "a");
	return tee_file;
}
int tee_shutdown() { return fclose(tee_file); }
FILE* tee_getFile() { return tee_file; }
void tee(const char* fmt, ...) { 
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    va_start(ap, fmt);
    vfprintf(tee_file, fmt, ap);
    va_end(ap);
	fflush(tee_file);
}

static FILE* flog_file = NULL;
FILE* flog_init(const char* file) {
	flog_file = fopen(file, "a");
	return flog_file;
}
int flog_shutdown() { return fclose(flog_file); }
FILE* flog_getFile() { return tee_file; }
void flog(const char* fmt, ...) { 
    va_list ap;
    va_start(ap, fmt);
    vfprintf(flog_file, fmt, ap);
    va_end(ap);
	fflush(flog_file);
}

void teeNflog(const char* fmt, ...) { 
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    va_start(ap, fmt);
    vfprintf(tee_file, fmt, ap);
	fflush(tee_file);
	vfprintf(flog_file, fmt, ap);
	fflush(flog_file);
    va_end(ap);
}