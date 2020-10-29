#include <ansi.h>

inherit SKILL;

int valid_enable(string usage) { return  usage == "arrow"; }

int valid_learn(object me)
{
        return notify_fail("连珠箭法只能向郭靖请教(qingjiao)来学习！\n");    
}

string perform_action_file(string action)
{
        return __DIR__"lianzhu-arrow/" + action;
}                 

void skill_improved(object me)   
{
        int lvl;

        lvl = me->query_skill("lianzhu-arrow", 1);  
        if( lvl >= 50 &&  
            !query("can_perform/lianzhu-arrow/lianzhu", me) )   
        {
                tell_object(me, HIC "你通晓了连珠箭法「" HIR "连珠箭法" HIC "」的奥秘。\n" NOR);    
                set("can_perform/lianzhu-arrow/lianzhu", 1, me);  
        }
}
