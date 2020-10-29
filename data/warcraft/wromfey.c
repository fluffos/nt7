// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m细雨如丝[2;37;0m[2;37;0m", ({"dranet"}));        
        set("gender", "男性");                
        set("long", "今生若不执子之手 待来生愿与子偕老[2;37;0m
它是徐州柴火的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wromfey");
        set("owner_name", "徐州柴火");
        set_temp("owner", "wromfey");
        set_temp("owner_name", "徐州柴火");
        ::setup();
}
