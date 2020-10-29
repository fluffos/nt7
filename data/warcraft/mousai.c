// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[46;1m[1;32m小不丁点[2;37;0m[2;37;0m", ({"xxoo"}));        
        set("gender", "男性");                
        set("long", "一只快乐的小布丁。[2;37;0m
它是缪斯的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "mousai");
        set("owner_name", "缪斯");
        set_temp("owner", "mousai");
        set_temp("owner_name", "缪斯");
        ::setup();
}
