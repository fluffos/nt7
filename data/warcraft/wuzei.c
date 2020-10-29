// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"long"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是段誉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wuzei");
        set("owner_name", "段誉");
        set_temp("owner", "wuzei");
        set_temp("owner_name", "段誉");
        ::setup();
}
