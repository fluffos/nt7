// socket.c
// by Find.

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        mixed *status;
        string out;
        int n,i;

        if (! SECURITY_D->valid_grant(me, "(admin)")) 
                return 0;

        // write(dump_socket_status());

        out ="Fd    状态       类型      本地地址        远端地址           所有者\n"+
             "--  ---------  --------  ------------  ------------------ ---------------\n";

        status = socket_status();

        n = sizeof(status);

        for(i=0;i<n;i++)
                out += sprintf("%2d %|9s %|8s %|12s %|17s %O\n",
                        status[i][0],status[i][1],status[i][2],status[i][3],status[i][4],status[i][5]);
        printf("%s\n",out);

        printf("数据库状态：%s\n",db_status());
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : socket
 
列出当前每一个 LPC socket 的状态。
 
HELP
    );
    return 1;
}