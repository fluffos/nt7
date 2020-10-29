#include <ansi.h> 
#include <condition.h> 

inherit F_CLEAN_UP; 
inherit POISON; 

string name() { return "qs_poison"; } 
string chinese_name() { return "七伤拳内伤"; } 

string update_msg_others() 
{
       return HIW "$N" HIW "突然脚下一晃，好象是受了严重的内伤！\n" NOR; 
}

string update_msg_self() 
{
       return HIW "你脚下恍惚，精神不能集中，好象是中了阴毒的内伤！\n" NOR; 
}