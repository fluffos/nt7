// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m八抬大轿[2;37;0m[2;37;0m", ({"jiaozi"}));        
        set("gender", "男性");                
        set("long", "八抬大轿[2;37;0m
它是胡雪岩的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "superrich");
        set("owner_name", "胡雪岩");
        set_temp("owner", "superrich");
        set_temp("owner_name", "胡雪岩");
        ::setup();
}
