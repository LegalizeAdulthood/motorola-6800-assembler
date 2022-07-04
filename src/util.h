#ifndef UTIL_H
#define UTIL_H

void fatal(const char *str);
void error(const char *str);
void warn(const char *str);
int delim(char c);
char *skip_white(char *ptr);
void eword(int wd);
int emit(int byte);
void f_record();
void hexout(int byte);
void print_line();
int any(char c, const char *str);
char mapdn(char c);
int lobyte(int i);
int hibyte(int i);
int head(const char *str1, const char *str2);
int alpha(char c);
int alphan(char c);
int white(char c);
char *alloc(int nbytes);

#endif // UTIL_H
