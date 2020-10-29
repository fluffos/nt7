// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m大浪头[2;37;0m[2;37;0m", ({"dlt"}));        
        set("gender", "男性");                
        set("long", "好大的浪头[2;37;0m
它是无极拳头的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ljjwd");
        set("owner_name", "无极拳头");
        set_temp("owner", "ljjwd");
        set_temp("owner_name", "无极拳头");
        ::setup();
}
