// tianmo-jue.c 

inherit SKILL; 

#include <ansi.h> 

void create() { seteuid(getuid()); } 

string type() { return "knowledge"; } 

int practice_skill(object me) 
{
        return notify_fail("天魔诀只能靠学习来提高。\n");
}

void skill_improved(object me) 
{
        tell_object(me, HIR "杀!杀!杀！我要杀尽天下所有人!\n" NOR);
        addn("shen", -200, me);
}