// alchemy.c
#include <ansi.h>

inherit SKILL;

//string type() { return "technic"; }
string type() { return "knowledge"; } 

int valid_learn(object me)
{
        return 1;
}

void skill_improved(object me) 
{
        int level;

        level = me->query_skillo("linghun-zhili", 1);
        if( me->query_skillo("alchemy", 1) > 2399 && level < 1000 )
        {
                tell_object(me, HIM "由于灵魂之力未达到灵境，无法借助灵气之力，你的炼丹技艺无法提升。\n" NOR); 
                return;
        }

        if( me->query_skillo("alchemy", 1) > 2699 && level < 2000 )
        {
                tell_object(me, HIM "由于灵魂之力未达到神境，无法借助神之力，你的炼丹技艺无法提升。\n" NOR); 
                return;
        }

        if( me->query_skillo("alchemy", 1) > 2999 && level < 3000 )
        {
                tell_object(me, HIM "由于灵魂之力未达到天境，无法借助天地之力，你的炼丹技艺无法提升。\n" NOR); 
                return;
        }
}
