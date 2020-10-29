// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("修炼[2;37;0m[2;37;0m", ({"newbie"}));        
        set("gender", "男性");                
        set("long", "修炼[2;37;0m
它是欧阳修的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "newpro");
        set("owner_name", "欧阳修");
        set_temp("owner", "newpro");
        set_temp("owner_name", "欧阳修");
        ::setup();
}
