/*结构体数组*/
#include <stdio.h>
//求数组元素个数
#define ARRYA_SIZE(x) (sizeof(x)/sizeof(x[0]))
/*声明描述学生信息的结构体*/
typedef struct student {
    char name[30]; //姓名
    int age; //年龄
    int sex; //性别
}stu_t;
int main(void)
{
    /*1.定义两个学生信息的结构体变量*/
    //stu_t info[] = {{"关羽", 18, 1}, {"黄蓉", 16, 0}};
    stu_t info[] = {
        {
            .sex = 1,
            .age = 18,
            .name = "关羽"
        },
        {
            .sex = 0,
            .age = 16,
            .name = "黄蓉"
        }
    };
    for(int i = 0; i < ARRYA_SIZE(info); i++)
        printf("%s %d %d\n", info[i].name, info[i].age, info[i].sex);
    info[0].age++;
    info[1].age++;
    for(int i = 0; i < ARRYA_SIZE(info); i++)
        printf("%s %d %d\n", info[i].name, info[i].age, info[i].sex);
    return 0;
}
