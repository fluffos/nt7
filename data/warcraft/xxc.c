// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小四[2;37;0m[2;37;0m", ({"xxclong"}));        
        set("gender", "男性");                
        set("long", "万恶[2;37;0m
它是老子的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xxc");
        set("owner_name", "老子");
        set_temp("owner", "xxc");
        set_temp("owner_name", "老子");
        ::setup();
}
