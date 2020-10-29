// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("着骑[2;37;0m[2;37;0m", ({"along"}));        
        set("gender", "男性");                
        set("long", "一八[2;37;0m
它是狂加藤的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kuangs");
        set("owner_name", "狂加藤");
        set_temp("owner", "kuangs");
        set_temp("owner_name", "狂加藤");
        ::setup();
}
