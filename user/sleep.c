# include"kernel/types.h"
# include"user/user.h"

int main (int arg_num, char* argv[]){
	/*
	 * arg_num 是参数数量
	 * char* argv[]是字符串指针数组，指向输入的那一行命令行
	 */
	if(arg_num != 2){
		printf("sleep函数需要两个参数");
		exit(1);  // 异常退出
	}

	// 字符串变成整数
	int time = atoi(argv[1]);
	sleep(time);

	exit(0);
	
}
