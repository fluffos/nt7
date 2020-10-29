// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"dddd"}));        
        set("gender", "男性");                
        set("long", "一头麒麟[2;37;0m
它是段微情的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "viking");
        set("owner_name", "段微情");
        set_temp("owner", "viking");
        set_temp("owner_name", "段微情");
        ::setup();
}
