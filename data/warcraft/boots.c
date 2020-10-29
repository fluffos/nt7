// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m靴魔[2;37;0m[2;37;0m", ({"bootsboots"}));        
        set("gender", "男性");                
        set("long", "$HIR$靴魔[2;37;0m
它是魔靴的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "boots");
        set("owner_name", "魔靴");
        set_temp("owner", "boots");
        set_temp("owner_name", "魔靴");
        ::setup();
}
