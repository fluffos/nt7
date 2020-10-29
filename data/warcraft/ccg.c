// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"ccgg"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是学改的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ccg");
        set("owner_name", "学改");
        set_temp("owner", "ccg");
        set_temp("owner_name", "学改");
        ::setup();
}
