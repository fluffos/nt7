// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是暴雨的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "bla");
        set("owner_name", "暴雨");
        set_temp("owner", "bla");
        set_temp("owner_name", "暴雨");
        ::setup();
}
