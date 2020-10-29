// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火鸟[2;37;0m[2;37;0m", ({"lylyly"}));        
        set("gender", "女性");                
        set("long", "火鸟[2;37;0m
它是乐儿的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "piple");
        set("owner_name", "乐儿");
        set_temp("owner", "piple");
        set_temp("owner_name", "乐儿");
        ::setup();
}
