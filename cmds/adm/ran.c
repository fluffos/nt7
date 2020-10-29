// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// random.c

int help(object me);

int main(object me, string arg)
{
        int t, i, j, temp;
        int *a;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;
                
        if (! arg || sscanf(arg, "%d", t) != 1)
                return help(me);
                
        a = allocate(10);
        for (j = 0; j < 10; j++) 
                a[j] = 0;
                
        for (i = 0; i < 1000; i++) 
        {
                temp = random(t);
                // printf("random(%d) is : %d\n", t, temp);
                for (j = 0; j < 10; j++) 
                {
                        if (temp < t * (j + 1) / 10) 
                        {
                                a[j] = a[j] + 1;
                                break;
                        }
                }        
                
        }
        
        for (j = 0; j < 10; j++) 
                printf("%d : 个数为 %d\n", j, a[j]);
        
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : ran <number>

用处 : 测试随机函数的分布。
HELP
        );
        return 1;
}