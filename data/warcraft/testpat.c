// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞飞[2;37;0m[2;37;0m", ({"flydd"}));        
        set("gender", "男性");                
        set("long", "飞飞[2;37;0m
它是宠物飞飞的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "testpat");
        set("owner_name", "宠物飞飞");
        set_temp("owner", "testpat");
        set_temp("owner_name", "宠物飞飞");
        ::setup();
}
