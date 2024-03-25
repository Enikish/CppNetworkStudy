#定义变量,定义依赖
src=$(wildcard ./*.c)
#定义替换
objs=$(patsubst %.c, %.o, $(src))
target=app
$(target):$(objs)
	#gcc add.c times.c main.c -o app 
	$(CC) $(objs) -o $(target)
%.o:%.c
	# $<表示目标文件名，$@表示第一个依赖名
	$(CC) -c $< -o $@
.PHONY:clean
clean:
	rm $(objs) -f
