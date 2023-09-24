#include "kernel/types.h"
#include "user/user.h"

void run(int listenfd){
	// 传入一个文件描述符，指向的是pipe的读端

	int cin_num = 0;
        int first_num = 0;
        int pipes[2];
	int forked = 0;

	while(1){
		int read_ans = read(listenfd, &cin_num, 4);  // 首先就是不断地从文件描述符读取对应文件的num
		if (read_ans == 0){
			// 这里是读取完毕了，也可以理解为最后的递归的返回
			close(listenfd); // 关闭输入的文件描述fu
			if(forked){
				close(pipes[1]);
				int child_pid = getpid();
				wait(&child_pid);
			}
			exit(0);

		}



		if (first_num==0){
			first_num = cin_num;  // 第一个肯定是素数
			printf("prime %d\n", first_num);		
		}

		
		if(cin_num % first_num != 0){
			// 这里就是不是这个素数的倍数，那我就再次启动就好
			if(!forked){
				// 要考虑是否是z复制过的子进程
				pipe(pipes);  // 创建管道
				forked = 1;  //就是已经创建了
				int ret = fork();
				if (ret == 0){
					// 子进程
					close(pipes[1]);
					close(listenfd);
					run(pipes[0]);
				}else{
					close(pipes[0]);
				}
			}


			// 传递给下一邻居、
			write(pipes[1], &cin_num, 4);
		}
      
	}
}


int main(int arg_num, char* argv[]){
	int pipes[2];
	pipe(pipes);
	for(int i = 2; i<=35; i++){
		write(pipes[1], &i, 4);  // 从管道的1端写入
	}
	close(pipes[1]);
	run(pipes[0]);
	exit(0);

}
