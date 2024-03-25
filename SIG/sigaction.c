/**
 * #include <signal.h>

       int sigaction(int signum, const struct sigaction *act,
                     struct sigaction *oldact);
            功能:
                检查或改变信号的处理. 信号捕捉
            参数:
                signum:
                    需要捕捉的信号的编号或者宏值
                act:
                    捕捉到信号之后的处理动作
                oldact:
                    上一次对信号捕捉相关的设置, 一般不适用, 传递NULL
            return:
                成功: 0
                失败: -1
 * 
        struct sigaction {
            //回调函数
               void     (*sa_handler)(int); 
            //不常用
               void     (*sa_sigaction)(int, siginfo_t *, void *);
            //临时阻塞信号集, 在信号捕捉函数执行过程中, 临时阻塞某些信号
               sigset_t   sa_mask;
            //使用哪一个信号处理对捕捉到的信号进行处理
            //这个值可以是0, 表示使用sa_handler,也可以是SA_SIGINFO表示使用sa_siginfo
               int        sa_flags;
            //废弃
               void     (*sa_restorer)(void);
           };
*/