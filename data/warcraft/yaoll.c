// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("浪里狼[2;37;0m[2;37;0m", ({"yaolll"}));        
        set("gender", "男性");                
        set("long", "浪里狼[2;37;0m
它是药流量的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yaoll");
        set("owner_name", "药流量");
        set_temp("owner", "yaoll");
        set_temp("owner_name", "药流量");
        ::setup();
}
