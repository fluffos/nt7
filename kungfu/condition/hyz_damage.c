// hyz_damage.c 混元无极劲伤

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON; 

string name() { return "hyz_damage"; } 

string chinese_name() { return "混元无极劲内伤"; } 

string update_msg_others() 
{
        return HIW "$N" HIW "的脸色突然大为苍白，摇摇欲坠，似乎是内伤发作了！\n" NOR; 
}

string update_msg_self() 
{
        return HIW "忽然你一阵头晕目眩，你所中的混元无极劲内伤发作了！\n" NOR; 
}