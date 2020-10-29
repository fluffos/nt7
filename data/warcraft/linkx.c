// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m混沌[2;37;0m[2;37;0m", ({"hundun"}));        
        set("gender", "男性");                
        set("long", "$MAG$混沌[2;37;0m
它是沧海一粟的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "linkx");
        set("owner_name", "沧海一粟");
        set_temp("owner", "linkx");
        set_temp("owner_name", "沧海一粟");
        ::setup();
}
