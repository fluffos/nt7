// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m小跟班[2;37;0m[2;37;0m", ({"dtdg"}));        
        set("gender", "男性");                
        set("long", "带头大哥的小跟班。[2;37;0m
它是带头大哥的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jojox");
        set("owner_name", "带头大哥");
        set_temp("owner", "jojox");
        set_temp("owner_name", "带头大哥");
        ::setup();
}
