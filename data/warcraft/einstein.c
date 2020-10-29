// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m睡[2;37;0m[2;37;0m", ({"slept"}));        
        set("gender", "男性");                
        set("long", "sdasfdv[2;37;0m
它是爱因时代的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "einstein");
        set("owner_name", "爱因时代");
        set_temp("owner", "einstein");
        set_temp("owner_name", "爱因时代");
        ::setup();
}
