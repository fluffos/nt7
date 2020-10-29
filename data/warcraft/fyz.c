// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽[2;37;0m[2;37;0m", ({"myfy"}));        
        set("gender", "男性");                
        set("long", "魔幻兽[2;37;0m
它是菜比朱的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "fyz");
        set("owner_name", "菜比朱");
        set_temp("owner", "fyz");
        set_temp("owner_name", "菜比朱");
        ::setup();
}
