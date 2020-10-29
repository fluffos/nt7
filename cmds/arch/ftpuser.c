// ftpuser.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        mixed ftp_sockets;
        string msg, stat ="";

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;
                
        if (! find_object(FTP_D))
                return notify_fail("传输精灵(FTP_D)尚未启动。\n");

        ftp_sockets = FTP_D->query_sockets();

        if (! ftp_sockets || ! sizeof(ftp_sockets))
                return notify_fail("传输精灵(FTP_D)目前没有任何使用者连线。\n");
                
        msg = sprintf("%-3s %-12s %-17s %-8s %-s\n", "FD", "帐号", "连线位置", "状态", "最后指令"); 
        foreach(string fd, mixed val in ftp_sockets)
        {
                if (! undefinedp(val["retr"])) stat += "<下载中>";
                if (! undefinedp(val["stor"])) stat += "<上传中>";
                msg += sprintf("%3d %-12s %-17s %-8s %s\n",
                        fd,
                        (val["login"] ? val["user"]:"(未登入)"),
                        val["address"],
                        stat, 
                        (val["lastcmd"] || "(无)"),
                );
        }
        tell_object(me, msg);
        return 1;
}
