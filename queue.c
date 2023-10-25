/*队列*/
#include <stdio.h>
#include <stdlib.h>
/*声明描述队列属性的结构体*/
typedef struct queue {
    int *arr; //首地址
    int cap; //容量
    int size; //有效数据的个数
    int front; //前端(出队)
    int rear; //后端(入队)
}queue_t;
//1.定义分配内存和初始化队列函数
void queue_init(queue_t *queue, int cap)
{
    queue->arr = (int *)malloc(cap * sizeof(queue->arr[0]));//分配内存
    queue->cap = cap; //容量
    queue->size = 0; //无数
    queue->front = 0; 
    queue->rear = 0;
}
//2.释放内存并且恢复到初始状态
void queue_deinit(queue_t *queue)
{
    free(queue->arr);
    queue->cap = 0; 
    queue->size = 0; //无数
    queue->front = 0; 
    queue->rear = 0;

}
//3.判断是否满
//4.判断是否空
//5.入队
//6.出队
//7.获取有效数据的个数
//8.获取队首元素的值
//测试主函数
int main(void)
{
    //1.定义队列
    queue_t queue;

    //2.初始化队列
    queue_init(&queue, 10);

    //3.销毁队列
    queue_deinit(&queue);
    return 0;
}





