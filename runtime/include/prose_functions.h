#ifndef __prose_func_h
#define __prose_func_h

void print_var(VAR var, int newline);
void append(int source_id, VAR elem);
void toupper_str(int str_id);
void tolower_str(int str_id);
void inc(int num_id);
void dec(int num_id);
void scan(int type, VAR_ID elem);
#endif
