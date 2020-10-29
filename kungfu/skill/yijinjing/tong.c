// This program is a part of NT MudLIB
// shield.c 易筋经 一气通八脉

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill, qi, maxqi;


        if( query("family/family_name", me) != "少林派" )
                return notify_fail("你不是少林弟子，无法使用易筋经绝技。\n");

        if( target != me )
                return notify_fail("你只能用易筋经来激发一气通八脉 \n");

        if( (skill = (int)me->query_skill("yijinjing", 1)) < 100 )
                return notify_fail("你的易筋经等级不够。\n");

        if( query("eff_qi", me)*100/query("max_qi", me)>80 )
                return notify_fail("你伤势很轻，无法激励易筋经至高绝学。\n");

        if( query("eff_qi", me)*100/query("max_qi", me)<10 )
                return notify_fail("你内伤太重，无法激励易筋经至高绝学。\n");

        if( query("neili", me)<skill*5 || query("max_neili", me)<500 )
                return notify_fail("你的真气不够。\n");

        addn("neili", -skill*5, me);
        me->receive_damage("qi", 0);

        message_combatd(HIM "$N" HIM "默念易筋经的口诀: "
                            "元气,气存于内,放于外。"
                            "易筋,孕怀于息,舒于支....\n"
                        HIW "一股详和的白色罡气自头顶迅速"
                        HIW "游遍" HIW "$N" HIW "的奇经八脉！\n"
                        HIR "你的内伤刹那间大为好转！！\n" NOR, me);

        addn("max_neili", -skill/5, me);

        addn("eff_qi", skill*5, me);
        if( query("eff_qi", me)>query("max_qi", me) )
                set("eff_qi",query("max_qi",  me), me);
        set("qi", query("eff_qi",  me), me);

        if( me->is_fighting() ) me->start_busy(5+random(5));

        return 1;
}