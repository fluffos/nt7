// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("泥[2;37;0m[2;37;0m", ({"axx"}));        
        set("gender", "男性");                
        set("long", "sadadas[2;37;0m
它是胡萝卜的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kylin");
        set("owner_name", "胡萝卜");
        set_temp("owner", "kylin");
        set_temp("owner_name", "胡萝卜");
        ::setup();
}
