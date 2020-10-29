// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白马[2;37;0m[2;37;0m", ({"myhorse"}));        
        set("gender", "男性");                
        set("long", "白马[2;37;0m
它是魏岳的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "weiyue");
        set("owner_name", "魏岳");
        set_temp("owner", "weiyue");
        set_temp("owner_name", "魏岳");
        ::setup();
}
