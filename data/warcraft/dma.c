// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小马[2;37;0m[2;37;0m", ({"dmabb"}));        
        set("gender", "女性");                
        set("long", "小马[2;37;0m
它是大米啊的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dma");
        set("owner_name", "大米啊");
        set_temp("owner", "dma");
        set_temp("owner_name", "大米啊");
        ::setup();
}
