// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("谁谁谁[2;37;0m[2;37;0m", ({"sheisheishei"}));        
        set("gender", "男性");                
        set("long", "谁谁谁[2;37;0m
它是冷锋的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lengfeng");
        set("owner_name", "冷锋");
        set_temp("owner", "lengfeng");
        set_temp("owner_name", "冷锋");
        ::setup();
}
