
#include "led.h"
#include "cmd.h"

#include "mma8653.h"

cmd_t cmd_list[]=
{
    {"led1on", led1_on},
    {"led1off", led1_off},
    {"mmaid", mma8653_show_id},
    {"mmaxyz", mma8653_get_xyz},
};



cmd_t *find_cmd(char *input_cmd)
{
    int i = 0;
    int num = sizeof(cmd_list)/sizeof(cmd_list[0]);

    for(; i<num; i++)
    {
        if(!my_strcmp(input_cmd, cmd_list[i].cmd_name))
        {
            return &(cmd_list[i]);
        }
    }

    return (cmd_t *)0;
}




