

#ifndef __CMD_H__
#define __CMD_H__

typedef struct _tcmd
{
    char *cmd_name;
    void (*cmd_func)(void);
}cmd_t;

extern int my_strcmp(char *, char *);
extern cmd_t *find_cmd(char *input_cmd);


#endif
