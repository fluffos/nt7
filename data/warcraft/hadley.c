// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("巨根[2;37;0m[2;37;0m", ({"elysium"}));        
        set("gender", "男性");                
        set("long", "一条巨根[2;37;0m
它是哥白尼的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hadley");
        set("owner_name", "哥白尼");
        set_temp("owner", "hadley");
        set_temp("owner_name", "哥白尼");
        ::setup();
}
