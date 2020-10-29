// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("云初[2;37;0m[2;37;0m", ({"yun"}));        
        set("gender", "女性");                
        set("long", "云初[2;37;0m
它是泡泡的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "step");
        set("owner_name", "泡泡");
        set_temp("owner", "step");
        set_temp("owner_name", "泡泡");
        ::setup();
}
