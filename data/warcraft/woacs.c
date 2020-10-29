// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m黄金神龙[2;37;0m[2;37;0m", ({"shenlong"}));        
        set("gender", "男性");                
        set("long", "就是一条龙而已[2;37;0m
它是重小楼的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "woacs");
        set("owner_name", "重小楼");
        set_temp("owner", "woacs");
        set_temp("owner_name", "重小楼");
        ::setup();
}
