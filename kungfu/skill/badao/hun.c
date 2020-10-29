#include <ansi.h>

string name() { return HIW "刀魂" NOR; } 

inherit F_SSERVER; 

int perform(object me, object target)
{
        int skill;
        object ob;
        object weapon;
        
        if( query("neili", me)<8000 )
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("badao", 1) < 1500)
                return notify_fail("你的霸刀修为不够。\n");

        if (me->query_skill_mapped("blade") != "badao")
                return notify_fail("你还没有激发霸刀呢。\n");
                
        if (find_living(query("id", me) + "-daohun"))
                return notify_fail("你的刀魂还没有消失，暂时不能施展该招。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对！\n");

        skill = me->query_skill("badao", 1);
        addn("neili", -8000, me);

        message_combatd(HIY "\n$N" HIY "祭起手中" + weapon->name() + HIY "，刹那间华光四起，一道"
                        "白影从" + weapon->name() + HIY "中幻化而出 ……\n\n" NOR, me);

        // 设置刀魂
        ob = new("/kungfu/class/misc/daohun");
        ob->init_npc(me);
        ob->move(environment(me));

        me->start_busy(3);
        
        return 1;
}
