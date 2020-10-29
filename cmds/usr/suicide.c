// suicide.c

#include <ansi.h>

inherit F_CLEAN_UP;

protected int slow_suicide(object me);
protected int halt_suicide(object me);

int main(object me, string arg)
{
        object *inv;
        int i;
        if (me->is_busy())
                return notify_fail("你上一个动作还没完成。\n");

        inv = deep_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! userp(inv[i]) && ! playerp(inv[i])) continue;
                return notify_fail("你身上还有个大活人呢，想不开也别急呀？\n");
        }

        if (! arg)
        {
                write("You commit suicide.\n");
                return 1;
        }

        if (arg != "-f") 
                return notify_fail("自杀有两种，您是要永远死掉(-f)还是重新投胎？\n");

        write("您选择永远死掉的自杀方式，这个人物的资料将永远删除，请务必\n"
              "考虑清楚，确定的话请输入您的管理密码：");
        input_to("check_password", 1, me, 1);
        return 1;
}

protected void check_password(string passwd, object me, int forever)
{
        object link_ob;
        string old_pass;

        link_ob=query_temp("link_ob", me);
        old_pass=query("ad_password", link_ob);
        if (! stringp(old_pass) || crypt(passwd, old_pass) != old_pass)
        {
                write(HIR "密码错误！请注意，自杀必须输入管理密码。\n");
                return;
        }

        if (forever)
        {
                tell_object(me, HIR "\n你决定要自杀了，如果三十秒"
                            "钟内不后悔，就真的永别了。\n\n" NOR);
                set_temp("suicide/time", time(), me);
                set_temp("suicide/last", 0, me);
                set_temp("suicide/from", query_ip_number(me), me);
                me->start_busy((: slow_suicide, me :),
                               (: halt_suicide, me :));
        }
}

protected int slow_suicide(object me)
{
        object link_ob;
        int t;

        if (! objectp(me))
                return 0;

        t=time()-query_temp("suicide/time", me);
        if( t<query_temp("suicide/last", me) )
        {
                delete_temp("suicide/", me);
                return 0;
        }

        if (t < 30)
        {
                if( t-query_temp("suicide/last", me)<5 )
                        return 1;

                tell_object(me, HIR "\n你还有" + chinese_number(30 - t) +
                            "秒钟仔细考虑(" HIC "halt停止" HIR ")。\n" NOR);
                set_temp("suicide/last", t/5*5, me);
                return 1;
        }

        link_ob=query_temp("link_ob", me);
        if (! link_ob || ! interactive(me)) return 0;

        log_file("static/suicide",
                 sprintf("%s %s commits a suicide from %s\n",
                        log_time(), log_id(me),
                        query_temp("suicide/from", me)));

        seteuid(getuid());
        write("\n好吧，永别了:)。\n\n");

        if( query("mud_age", me)>1800 )
        CHANNEL_D->do_channel(this_object(), "rumor",
                sprintf("%s自杀了，以后你再也看不到这个人了。",
                me->name()));

        tell_room(environment(me), me->name() +
                "在你的面前化作轻烟，渐渐消失了...\n", ({me}));

        UPDATE_D->remove_user(query("id", me), 1);
        return 0;
}

protected int halt_suicide(object me)
{
        tell_object(me, HIG "你打消了寻死的念头。\n" NOR);
        delete_temp("suicide", me);
        return 1;
}

int help (object me)
{
        write(@HELP
指令格式: suicide [-f]
 
如果因为某种原因你不想活了, 你可以选择自杀.
自杀分两种:
 
suicide    : 重新投胎
suicide -f : 永远的除去玩家资料, 系统会要求你
             输入密码以确认身份.
 
请慎重选择 :)
 
HELP );
        return 1;
}
