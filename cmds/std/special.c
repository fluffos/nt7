// special

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string  msg;
        mapping ss;
        string  skill;
        object ob;
        string pro;
        int i;
        string tmp_msg;

        if (wizardp(me) && stringp(arg) &&
            objectp(ob = find_player(arg)))
                // 查看其他玩家的特殊技能
                arg = 0;
        else
                ob = me;

        pro = (ob == me) ? "你" : ob->name(1);

        if( !query("born", ob) )
                return notify_fail(pro + "还没有出生呐，会什么特技？\n");

        if( !mapp(ss=query("special_skill", ob)) || 
            ! sizeof(ss))
                return notify_fail(pro + "现在好像什么特技都不会哦。\n");

        if (arg && (ob == me))
        {
                // 有参数，运用特技。
                if (me->is_busy())
                        return notify_fail("你现在忙着呢，不能使用特技。\n");

                if (sscanf(arg, "%s %s", skill, arg) != 2)
                        skill = arg;

                if( !query("special_skill/"+skill, me) )
                        return notify_fail("你不会这种特技啊！\n");

                if (file_size(SPECIAL_D(skill) + ".c") < 0 
                    && file_size("/kungfu/special2/" + skill + ".c") < 0)
                        return notify_fail("好像没有这种特技...\n");

                if (file_size("/kungfu/special2/" + skill + ".c") != -1)
                          return ("/kungfu/special2/" + skill)->perform(me, skill, arg);

                return SPECIAL_D(skill)->perform(me, skill, arg);
        }

        msg = pro + "现在会以下这些特技：\n";
        i = 1;
        foreach (skill in keys(ss))
        {
                if (file_size(SPECIAL_D(skill) + ".c") < 0
                    && file_size("/kungfu/special2/" + skill + ".c") < 0)
                {
                        write("不存在技能：" + skill + "\n");
                        continue;
                }
                // 如果大于7个则每行显示四个                                
                if (file_size("/kungfu/special2/" + skill + ".c") != -1)
                {
                        if( sizeof(query("special_skill", ob)) >= 7 )
                        {
                                tmp_msg = ("/kungfu/special2/" + skill)->name() +  "(" YEL + skill + NOR ")";
                                msg += sprintf("%-28s", tmp_msg);
                                if (i % 4 == 0 && i > 1)msg += "\n";
                        }
                        else
                        {
                                msg += ("/kungfu/special2/" + skill)->name() +  "(" YEL + skill + NOR ")\n";
                        }
                }

                else
                {
                        if( sizeof(query("special_skill", ob)) >= 7 )
                        {
                                tmp_msg = SPECIAL_D(skill)->name() + "(" YEL + skill + NOR ")";
                                msg += sprintf("%-28s", tmp_msg);
                                if (i % 4 == 0 && i > 1)msg += "\n";
                        }
                        else
                        {
                                msg += SPECIAL_D(skill)->name() + "(" YEL + skill + NOR ")\n";
                        }
                }
                
                i += 1;
                
        }
        write(msg + "\n");
        return 1;
}

int help(object me)
{
write(@HELP
指令格式 : special <skill> | <玩家ID>

使用这条命令可以查看你的特技，如果要运用你的特技，则可以加上
参数指名使用什么特技。比如：special hatred，运用杀气。

巫师可以查看其他玩家所会的特殊技能。

HELP );
    return 1;
}
