// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("雨[2;37;0m[2;37;0m", ({"logo"}));        
        set("gender", "女性");                
        set("long", "   [2;37;0m
它是精力无限的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "log");
        set("owner_name", "精力无限");
        set_temp("owner", "log");
        set_temp("owner_name", "精力无限");
        ::setup();
}
