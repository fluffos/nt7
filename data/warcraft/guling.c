// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("烟都[2;37;0m[2;37;0m", ({"shiyan"}));        
        set("gender", "男性");                
        set("long", "烟都大宗师[2;37;0m
它是古陵逝烟的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "guling");
        set("owner_name", "古陵逝烟");
        set_temp("owner", "guling");
        set_temp("owner_name", "古陵逝烟");
        ::setup();
}
