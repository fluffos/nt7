// pique.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int pts, max_pts;

        pts = 0;
        if (! arg || (arg != "none" && ! sscanf(arg, "%d", pts)))
                return notify_fail("指令格式：pique|jianu <使出几成愤怒伤敌>|none\n");

        max_pts = me->query_max_craze() / 100;
        if (max_pts < 1)
                return notify_fail("你的性格不合，无法使用愤怒攻击。\n");

        if (pts > max_pts)
                return notify_fail("你每次出招只能使出 " + max_pts +
                                   " 点愤怒。\n");
        if (pts == 0)
                delete("jianu", me);
        else
                set("jianu", pts, me);

        write("Ok.\n");
        return 1;
}

int help (object me)
{
        write(@HELP
指令格式: pique|jianu <使出几点愤怒伤敌>|none
 
这个指令让你指定每次击中敌人时，要发出几点愤怒以伤害对方。如
果使用了愤怒伤敌，则在攻击中还有一定的几率可以使出愤怒必杀技
暴怒招式。

pique none 则表示你不使用愤怒。

HELP );
        return 1;
}