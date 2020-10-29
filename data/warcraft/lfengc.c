// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神仙狗[2;37;0m[2;37;0m", ({"shengou"}));        
        set("gender", "男性");                
        set("long", "神仙狗[2;37;0m
它是凤帽子的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lfengc");
        set("owner_name", "凤帽子");
        set_temp("owner", "lfengc");
        set_temp("owner_name", "凤帽子");
        ::setup();
}
