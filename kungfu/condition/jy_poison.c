#include <ansi.h> 
#include <condition.h> 

inherit F_CLEAN_UP; 
inherit POISON; 

string name() { return "jy_poison"; } 
string chinese_name() { return "九阴白骨爪毒"; } 

string update_msg_others() 
{
       return BLU "$N" BLU "突然只膝弯曲，身子慢慢垂下，口中发出似人似鬼的荷荷之声。\n" NOR; 
}

string update_msg_self() 
{
       return BLU "你忽然感到身体僵直，已经不听使唤了。\n" NOR; 
}