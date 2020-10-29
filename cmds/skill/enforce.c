// enforce.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int pts;
        int max;

        if( !arg || (arg!="none" && arg!="max" && !sscanf(arg, "%d", pts)) )
                return notify_fail("指令格式：enforce|jiali <使出几成内力伤敌>|none|max\n");

        if( !me->query_skill_mapped("force") )
                return notify_fail("你必须先 enable 一种内功。\n");

        max = (int)me->query_skill("force") / 2;
        // 狂暴之力增加加力上限 
        if (query("special_skill/might", me)) 
                max += max * 20 / 100;

        max += me->query_all_buff("jiali");

        if( arg=="none" )
                delete("jiali", me);
        else
        if( arg=="max" )
                set("jiali", max, me);
        else {
                if( pts < 0 || pts > max )
                        return notify_fail("你只能用 none 表示不运内力，或数字表示每一击用几点内力。\n");
                set("jiali", pts, me);
        }

        write("Ok.\n");
        return 1;
}

int help (object me)
{
        write(@HELP
指令格式: enforce|jiali <使出几点内力伤敌>|none|max

这个指令让你指定每次击中敌人时，要发出几点内力伤敌。

enforce none 则表示你不使用内力。
enforce max 则表示你使用最大内力。

See Also: enable
HELP );
        return 1;
}
