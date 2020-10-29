// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("兽兽[2;37;0m[2;37;0m", ({"sshou"}));        
        set("gender", "男性");                
        set("long", "兽兽[2;37;0m
它是古越龙山的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "cauac");
        set("owner_name", "古越龙山");
        set_temp("owner", "cauac");
        set_temp("owner_name", "古越龙山");
        ::setup();
}
