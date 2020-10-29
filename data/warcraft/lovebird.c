// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m雷龙[2;37;0m[2;37;0m", ({"birdbird"}));        
        set("gender", "男性");                
        set("long", "雷龙[2;37;0m
它是慕鸟飞的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lovebird");
        set("owner_name", "慕鸟飞");
        set_temp("owner", "lovebird");
        set_temp("owner_name", "慕鸟飞");
        ::setup();
}
