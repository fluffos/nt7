// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小母龙[2;37;0m[2;37;0m", ({"mulong"}));        
        set("gender", "女性");                
        set("long", "$HIM$绝代娇龙[2;37;0m
它是龙组长风的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lst");
        set("owner_name", "龙组长风");
        set_temp("owner", "lst");
        set_temp("owner_name", "龙组长风");
        ::setup();
}
