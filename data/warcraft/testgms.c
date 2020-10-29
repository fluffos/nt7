// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽[2;37;0m[2;37;0m", ({"gmsss"}));        
        set("gender", "男性");                
        set("long", "一只普通魔幻兽。[2;37;0m
它是飞流三尺的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "testgms");
        set("owner_name", "飞流三尺");
        set_temp("owner", "testgms");
        set_temp("owner_name", "飞流三尺");
        ::setup();
}
