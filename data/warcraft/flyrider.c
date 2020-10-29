// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄龟[2;37;0m[2;37;0m", ({"xgui"}));        
        set("gender", "女性");                
        set("long", "hi[2;37;0m
它是飞烟的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "flyrider");
        set("owner_name", "飞烟");
        set_temp("owner", "flyrider");
        set_temp("owner_name", "飞烟");
        ::setup();
}
