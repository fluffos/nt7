// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("钱[2;37;0m[2;37;0m", ({"money"}));        
        set("gender", "男性");                
        set("long", "钱[2;37;0m
它是钱一的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "golda");
        set("owner_name", "钱一");
        set_temp("owner", "golda");
        set_temp("owner_name", "钱一");
        ::setup();
}
