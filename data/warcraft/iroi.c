// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火鸟[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "女性");                
        set("long", "一只小小鸟。。。。。。[2;37;0m
它是剑道的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "iroi");
        set("owner_name", "剑道");
        set_temp("owner", "iroi");
        set_temp("owner_name", "剑道");
        ::setup();
}
