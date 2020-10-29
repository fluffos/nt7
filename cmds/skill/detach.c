// detach.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        mapping family, skills;
        int i;
        string *skname;
        int lvl = 0;

        if (me->is_busy())
                return notify_fail("你现在正忙着呢。\n");

        if (! arg)
                return notify_fail("指令格式：detach <对象>\n");

        if (! (ob = present(arg, environment(me))) ||
            ! ob->is_character())
                return notify_fail("你想和谁断绝师徒关系？?\n");

        if (! living(ob))
                return notify_fail("你必须先把" + ob->name() + "弄醒。\n");

        if( query("reborn_offer", me) )
                return notify_fail("转世进程中不可以脱离门派。\n");

        if( query_temp("pending/detach", me) != ob )
        {
                write(HIR "你真的打算和" + ob->name(1) + "说你要离开师门吗？倘若真"
                      "的离开了，你将会失去所有的高级武功哦！\n" NOR);
                write(YEL "如果你真的下了决心，就请再输入一次这个命令。\n" NOR);
                set_temp("pending/detach", ob, me);
                me->start_busy(1);
                return 1;
        }

        if (! me->is_apprentice_of(ob))
        {
                if( query("family/family_name", ob) == query("family/family_name", me) )
                {
                    message_vision("\n$N大吃一惊，对$n道：什，什么？你要脱离师门？"
                                   "这事可得找你师傅去。\n", ob, me);
                    return 1;
                }
        }

        message_vision("\n$N向$n磕了一个头，道：师父！我... 我想脱离师门。\n", me, ob);
        if( intp(query("family/beggarlvl", me)) && 
            query("family/beggarlvl", me)>0 )
                lvl=query("family/beggarlvl", me);
        set_temp("pending/detach", 1, me);
        tell_object(ob, me->name() + "想脱离师门。\n");
        ob->attempt_detach(me);
        if (lvl) set("gaibang/beggarlvl", lvl, me); 
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : detach|tuoli <对象>
 
这个指令能让你向你的师傅请求脱离师门，因为一般的大门派不愿意接
收判师的人，所以如果你想改投其他门派，最好按照规矩脱离师门，然
而一旦脱离师门，师傅将追回你所有学到的本门秘学，并追回部分其他
武功，知识不会受到任何影响。

请参考相关指令 expell
HELP );
        return 1;
}
