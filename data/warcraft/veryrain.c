// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("兔子[2;37;0m[2;37;0m", ({"rabbit"}));        
        set("gender", "男性");                
        set("long", "一只兔子[2;37;0m
它是剑雨的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "veryrain");
        set("owner_name", "剑雨");
        set_temp("owner", "veryrain");
        set_temp("owner_name", "剑雨");
        ::setup();
}
