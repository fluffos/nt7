// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"long"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是不为人有的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lingjiu");
        set("owner_name", "不为人有");
        set_temp("owner", "lingjiu");
        set_temp("owner_name", "不为人有");
        ::setup();
}
