// longhe.c

#include <ansi.h>

int exert(object me, object target)
{
        int level = me->query_skill("linji-zhuang", 1);
        int jingli, jing, extrajing;

        if (level < 90) return notify_fail("你的临济十二庄修为还不够。\n");

        if( query("max_neili", me)<5*level )
                return notify_fail("你的内力还不够强。\n");

        if( query("eff_qi", me)<query("max_qi", me)/2 )
                return notify_fail("你已经受伤过重，只怕一运真气便有生命危险！\n");

        if( query("eff_jing", me)<query("max_jing", me)/2 )
                return notify_fail("你已经受伤过重，只怕一运真气便有生命危险！\n");

        extrajing=query("jing", me)-query("max_jing", me)/2;
        if (extrajing < 1)
                return notify_fail("你的精神太差。");

        if( query("neili", me)<1 )
                return notify_fail("你的真气不够。\n");

        jingli=query("max_jingli", me)-query("jingli", me);
        if ( jingli < 10 )
                return notify_fail("你现在精力充沛。\n");
        jing = 90*jingli/level;
        if (jing < 5) jing = 5;
        if (extrajing < jing) {
                jingli = jingli * extrajing / jing;
                jing = extrajing ;
        }
        addn("jing", -jing, me);
        addn("jingli", jingli, me);

        write( HIY "你暗运龙鹤两庄，启天门，闭地户，聚精成力，顿觉气力倍增。\n" NOR);
        message("vision",
                HIY + "只见" + me->name() + "稍显疲乏，但转瞬间便精神抖擞。\n" NOR,
                environment(me), me);

        return 1;
}