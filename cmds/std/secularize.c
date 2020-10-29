// secularize.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        if( query("class", me) != "bonze" )
                return 0;

        if( stringp(query("family/family_name", me)) && 
            (query("family/family_name", me) == "少林派" || 
            query("family/family_name", me) == "峨嵋派") )
        {
                write("你没有禀告师长，怎敢擅自还俗？\n");
                return 1;
        }

        if( query_temp("pending/secularize", me) )
        {
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "听说" + me->name(1) + "厌倦了清贫枯燥的生活，决定还俗。");
                delete("class", me);
                write("你摸了摸脑袋，叹了口气，决定回尘世好好享受享受。\n");

                if( stringp(query("purename", me)) )
                        me->set_name();
                return 1;
        }

        set_temp("pending/secularize", 1, me);
        write(YEL "你决定要还俗吗？这可是大事，如果你下了决心，那就再输入一次这个命令。\n" NOR);
        return 1;
}

int help (object me)
{
        write(@HELP
指令格式: secularize|huansu
 
这个指令让你放弃无聊的出家生活。

HELP );
        return 1;
}