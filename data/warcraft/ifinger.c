// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙[2;37;0m[2;37;0m", ({"long"}));        
        set("gender", "男性");                
        set("long", "龙[2;37;0m
它是指套师傅的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ifinger");
        set("owner_name", "指套师傅");
        set_temp("owner", "ifinger");
        set_temp("owner_name", "指套师傅");
        ::setup();
}
