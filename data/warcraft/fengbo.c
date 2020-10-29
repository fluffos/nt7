// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞龙在天[2;37;0m[2;37;0m", ({"feilong"}));        
        set("gender", "男性");                
        set("long", "一只青龙[2;37;0m
它是风雪飘飞的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "fengbo");
        set("owner_name", "风雪飘飞");
        set_temp("owner", "fengbo");
        set_temp("owner_name", "风雪飘飞");
        ::setup();
}
