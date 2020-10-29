// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("汇金[2;37;0m[2;37;0m", ({"along"}));        
        set("gender", "男性");                
        set("long", "文化[2;37;0m
它是狂七的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kuangg");
        set("owner_name", "狂七");
        set_temp("owner", "kuangg");
        set_temp("owner_name", "狂七");
        ::setup();
}
