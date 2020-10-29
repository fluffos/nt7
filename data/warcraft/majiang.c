// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麻神麒麟[2;37;0m[2;37;0m", ({"majiangride"}));        
        set("gender", "男性");                
        set("long", "麻神麒麟[2;37;0m
它是麻将的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "majiang");
        set("owner_name", "麻将");
        set_temp("owner", "majiang");
        set_temp("owner_name", "麻将");
        ::setup();
}
