// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("诗水蛇山[2;37;0m[2;37;0m", ({"qqhxz"}));        
        set("gender", "女性");                
        set("long", "是生是死[2;37;0m
它是山水三少的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "qhxz");
        set("owner_name", "山水三少");
        set_temp("owner", "qhxz");
        set_temp("owner_name", "山水三少");
        ::setup();
}
