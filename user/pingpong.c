# include "kernel/types.h"
# include "user/user.h"

int main(int arg_num, char* argv[]){
        // 实现父进程和子进程的通信
        int p1[2], p2[2];  // 0是写出，1是写入;1是子向父
        pipe(p1);
        pipe(p2);
        char buf[] = {"a"};
        int pid[2];// 0是子，1是父
        int fok = fork();
        if(fok == 0){
                // 子进程
                pid[0] = getpid();
                close(p1[0]);  // 关闭p1的读端
                close(p2[1]);  // 关闭p2的写端
                read(p2[0], buf, 1);
                printf("%d: received ping\n",pid[0]);
                write(p1[1], buf, 1);
                exit(0);
        }else{

                pid[1] = getpid();
                close(p1[1]);  // 关闭p1的写端
                close(p2[0]);  // 关闭p2的读端
                write(p2[1], buf, 1);
                read(p1[0], buf, 1);
                printf("%d: received pong\n",pid[1]);
                exit(0);
        }

}
