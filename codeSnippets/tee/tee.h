#ifndef TEE_H
#define TEE_H

extern FILE* tee_init(const char*);
extern int tee_shutdown();
extern void tee(char const*, ...);
extern FILE* tee_getFile();

extern FILE* flog_init(const char*);
extern int flog_shutdown();
extern void flog(char const*, ...);
extern FILE* flog_getFile();

#endif