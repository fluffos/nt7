// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("轻轻龙[2;37;0m[2;37;0m", ({"longq"}));        
        set("gender", "男性");                
        set("long", "一只蛇而已[2;37;0m
它是胡碟的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "butter");
        set("owner_name", "胡碟");
        set_temp("owner", "butter");
        set_temp("owner_name", "胡碟");
        ::setup();
}
