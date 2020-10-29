// tiandi.c

#include <ansi.h>

int exert(object me, object target)
{
        int level = me->query_skill("linji-zhuang", 1);

        if (level < 30) return notify_fail("你的临济十二庄修为还不够。\n");

        if (me->is_fighting())
                return notify_fail("战斗中不能运用天地二庄。\n");

        if( query("max_neili", me)<5*level )
                return notify_fail("你的内力还不够强。\n");

        if( query("neili", me)<4*level )
                return notify_fail("你的真气不够。\n");

        if( query("eff_qi", me)<query("max_qi", me)/2 )
                return notify_fail("你已经受伤过重，只怕一运真气便有生命危险！\n");

        if( query_temp("linji/tiandi", me) )
                return notify_fail("你已经运用天地二庄聚精气于身了。\n");

        set_temp("linji/tiandi", 1, me);
        write( HIY "你席地而坐，五心向天，运行天地二庄，益气升阳，益阴潜阳，升降反正，天地二气交泰于身，顿觉自己精气上限增加了。\n" NOR);
        message_combatd(
                HIY + "只见" + me->name() + "席地而坐，五心向天，脸上红光时隐时现，不一会儿便神采弈弈地站了起来。\n" NOR,
                me);

        addn("max_qi", level*10, me);
        addn("max_jing", level*10, me);
        me->receive_curing("qi", level*10);
        me->receive_curing("jing", level*10);
        addn("jingli", level, me);
        addn("neili", -4*level, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, level :), 600);

        return 1;
}

void remove_effect(object me, int level)
{
        addn("max_qi", -level*10, me);
        addn("max_jing", -level*10, me);
        if( query("eff_qi", me)>query("max_qi", me) )
                set("eff_qi",query("max_qi",  me), me);
        if( query("eff_jing", me)>query("max_jing", me) )
                set("eff_jing",query("max_jing",  me), me);
        delete_temp("linji/tiandi", me);

        tell_object(me, HIG"你所聚天地之精气已散回天地之间，你又恢复了原有精气。\n"NOR);
}