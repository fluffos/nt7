// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("文化[2;37;0m[2;37;0m", ({"along"}));        
        set("gender", "男性");                
        set("long", "海东[2;37;0m
它是狂一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kuanga");
        set("owner_name", "狂一");
        set_temp("owner", "kuanga");
        set_temp("owner_name", "狂一");
        ::setup();
}
