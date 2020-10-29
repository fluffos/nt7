// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞机依[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "飞机依[2;37;0m
它是丰鸡的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "iankg");
        set("owner_name", "丰鸡");
        set_temp("owner", "iankg");
        set_temp("owner_name", "丰鸡");
        ::setup();
}
