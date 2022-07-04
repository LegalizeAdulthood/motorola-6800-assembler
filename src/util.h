#ifndef UTIL_H
#define UTIL_H

void fatal(const char *str);
void error(const char *str);
void warn(const char *str);
int delim(char c);
char *skip_white(char *ptr);
void eword(int wd);
int emit(int byte);
void f_record(void);
void hexout(int byte);
void print_line(void);
int any(char c, char *str);
char mapdn(char c);
int lobyte(int i);
int hibyte(int i);
int head(char *str1, char *str2);
int alpha(char c);
int alphan(char c);
int white(char c);
char *alloc(int nbytes);

#endif // UTIL_H
