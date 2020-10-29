// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞飞[2;37;0m[2;37;0m", ({"flydd"}));        
        set("gender", "男性");                
        set("long", "飞飞[2;37;0m
它是飞宠物的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "testpata");
        set("owner_name", "飞宠物");
        set_temp("owner", "testpata");
        set_temp("owner_name", "飞宠物");
        ::setup();
}
