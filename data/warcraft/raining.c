// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m烟[5m[1;36m雨[1;35m飘[1;33m落[2;37;0m[2;37;0m[2;37;0m", ({"rains"}));        
        set("gender", "女性");                
        set("long", "烟雨飘落[2;37;0m
它是暴风雨的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "raining");
        set("owner_name", "暴风雨");
        set_temp("owner", "raining");
        set_temp("owner_name", "暴风雨");
        ::setup();
}
