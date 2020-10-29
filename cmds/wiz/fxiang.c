// fxiang.c
// created by ken

#include <ansi.h> 
#include <getconfig.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string *file;
        string *xiang;
        string msg;
        string board;
        int i, j, l = 0;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        seteuid(getuid());

        file = map_array(get_dir("/data/room/"), (: "/data/room/" + $1 +"/woshi.c":));
        xiang = map_array(get_dir("/data/room/"), (: $1 :) );
        i = sizeof(file);
        if (! i)
        {
                write("目前没有任何宝箱。\n");
                return 1;
        }

        if (arg)
        {
                sscanf(arg, "%d", j);
                j--;
                if (j < 0 || j >= i)
                        return notify_fail("没有这个宝箱。\n");

                me->force_me("goto " + file[j]);
                me->force_me("look baoxiang");
                return 1; 
        }

        msg = "目前" + LOCAL_MUD_NAME() + "的宝箱有以下这些：\n";
        for (j = 0; j < i; j++)
        {
                msg += sprintf(HIY "%3d" NOR ". %10s", j + 1, xiang[j] );
                l = l + 1;
                if (l > 5)
                {
                        msg += sprintf("\n");
                        l = 0;
                }
        }
        msg += "用 fxiang n 去看你想看的宝箱。\n";
        write(msg);
        return 1;
}
