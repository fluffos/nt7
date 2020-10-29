// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("嗜血天娇[2;37;0m[2;37;0m", ({"tjcw"}));        
        set("gender", "女性");                
        set("long", "嗜血天娇[2;37;0m
它是独孤天骄的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dgtj");
        set("owner_name", "独孤天骄");
        set_temp("owner", "dgtj");
        set_temp("owner_name", "独孤天骄");
        ::setup();
}
