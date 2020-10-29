// redl 2014
#include <ansi.h>
inherit F_CLEAN_UP;

int help(object me);

void create()
{
        seteuid(getuid());
}

int main(object me, string arg)
{
        object obj;
        string no_tell, can_tell;

        if (me->is_busy()) 
                return notify_fail("你现在正忙着呢。\n");
 
                me->start_busy(5); 
 
        if( wiz_level(me) < 1 )
                return notify_fail("你没有这个权力。\n");

        if (! arg || arg == "")
                return notify_fail("你是打算禁闭谁？\n");

        if( arg == query("id", me) )
                return notify_fail("你有病？\n");

        obj = find_player(arg);

        if (! obj || ! me->visible(obj)) 
                return notify_fail("没有这个人。\n");

          if ( wiz_level(obj) >= wiz_level(me) )
                return notify_fail("你权限不足。\n");


                tell_object(me, "注意：\n只能惩罚chat频道刷屏的人，禁止滥用，\n对于聊天室里非chat的刷屏者，先使用push来制止。\n如果确定要继续使用输入y:\n"); 
                input_to("get_input", me, obj);

        return 1;
}

int do_beep(object obj)
{
        if (! obj) return 1;
        tell_object(obj, "\a", 0);
        return 1;
}

protected void get_input(string arg, object me, object obj)
{
        if (!arg || arg!="y") {
                tell_object(me, "你宽容地打消了念头。\n"); 
                return;
        }
        call_out("do_beep", 1, obj); 
        call_out("do_beep", 2, obj); 
        call_out("do_beep", 3, obj); 
        call_out("do_beep", 4, obj); 
    set("active",0,obj);
        get_object("/u/redl/prison")->throw_flood(me, obj); 
}


int help(object me)
{
        write(@HELP
指令格式：throwf <某人>

因为某人刷屏而禁闭他一段时间，惩罚时间递增，有记录。（导师权限以上可用）

HELP);
        return 1;
}


