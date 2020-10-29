// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小龙[2;37;0m[2;37;0m", ({"xql"}));        
        set("gender", "男性");                
        set("long", "图腾[2;37;0m
它是飞鸟的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lmmlz");
        set("owner_name", "飞鸟");
        set_temp("owner", "lmmlz");
        set_temp("owner_name", "飞鸟");
        ::setup();
}
