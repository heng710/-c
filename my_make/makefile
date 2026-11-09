.PHONY:clean



TARGET=demo
OBJS=main.o a.o b.o


# 内置变量
CC  = gcc # C编译器名称
CFLAGS  = -O2 -Wall -I inc/ # C编译选项
LDFLAGS = -lm # 链接器参数

demo:$(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

#静态规则
$(OBJS):%.o:%.c
	$(CC) $^ -o $@ -c $(CFLAGS)

clean:
	rm $(TARGET) $(OBJS)