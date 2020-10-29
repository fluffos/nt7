
// port.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object *ob;
        string str;
        int i, I1, I2, I3, I4;
        
        ob = filter_array(children(USER_OB),(: userp :));
        str = HBRED"以下为本游戏各端口使用情况，其中 4000 为大五码(BIG5)专用端口。\n"NOR;
        for(i=0;i<sizeof(ob);i++){
                if(!environment(ob[i])) continue;
                if(query_ip_port(ob[i]) == 6000) I1++;
                if(query_ip_port(ob[i]) == 9000) I2++;
                if(query_ip_port(ob[i]) == 7000) I3++;
                if(query_ip_port(ob[i]) == 8000) I4++;
        }

        str += sprintf(HBRED"    " CYN "│6000：" HIW "%3d" CYN "人│7000：" HIW"%3d" CYN "人│8000："HIW "%3d" CYN"人|9000： "HIW "%3d" CYN "人|     \n" NOR,I1,I3,I4,I2);

        write(NOR + str + "\n");
        return 1;
}

int help(object me)
{
        write(@HELP

指令格式：port

这个指令是让你了解目前游戏中各端口的使用程度。为了给您提供一个流
畅的网络环境，建议选择使用率较低的端口连线。

HELP
        );
        return 1;
}

