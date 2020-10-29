// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m长[1;33m河[1;36m落[1;34m日[2;37;0m[2;37;0m", ({"ture"}));        
        set("gender", "女性");                
        set("long", "邵五丰的飞天坐骑，看上去深不可测，已有大乘境界。[2;37;0m
它是邵五丰的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "winjoesan");
        set("owner_name", "邵五丰");
        set_temp("owner", "winjoesan");
        set_temp("owner_name", "邵五丰");
        ::setup();
}
