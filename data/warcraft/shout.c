// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("肥肥[2;37;0m[2;37;0m", ({"fatfat"}));        
        set("gender", "男性");                
        set("long", "肥肥[2;37;0m
它是大喝的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "shout");
        set("owner_name", "大喝");
        set_temp("owner", "shout");
        set_temp("owner_name", "大喝");
        ::setup();
}
