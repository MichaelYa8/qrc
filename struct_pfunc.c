/*结构体和函数指针*/
#include <stdio.h>
//此声明告诉gcc stu_t声明在下面,前面需要用到
typedef struct student stu_t;
//声明函数指针数据类型
typedef void (*pfunc_t)(stu_t *);
//声明结构体
typedef struct student {
    char name[30]; //姓名 
    int age; //年龄
    int sex; //性别
    pfunc_t pfunc1; //函数指针变量将来指向一个操作函数
    pfunc_t pfunc2; //函数指针变量将来指向一个操作函数
}stu_t;
//定义打印学生信息函数show和grow
void show(stu_t *pstu){
    printf("%s %d %d\n", pstu->name, pstu->age, pstu->sex);
}
void grow(stu_t *pstu) {
    pstu->age++;
}
int main(void)
{
    //定义结构体变量描述学生信息
    stu_t  student1 = {
        .name = "刘备",
        .age = 19,
        .sex = 1,
        .pfunc1 = show, //指向show函数
        .pfunc2 = grow //指向grow函数
    };
    //调用student1学生的操作函数show和grow
    student1.pfunc1(&student1);
    student1.pfunc2(&student1);
    student1.pfunc1(&student1);
    return 0;
}
