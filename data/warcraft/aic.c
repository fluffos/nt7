// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("呼呼呼[2;37;0m[2;37;0m", ({"sss"}));        
        set("gender", "女性");                
        set("long", "呼呼呼[2;37;0m
它是阿二的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "aic");
        set("owner_name", "阿二");
        set_temp("owner", "aic");
        set_temp("owner_name", "阿二");
        ::setup();
}
