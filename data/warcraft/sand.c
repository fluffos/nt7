// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("宝马[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "奔驰开来了[2;37;0m
它是单思的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "sand");
        set("owner_name", "单思");
        set_temp("owner", "sand");
        set_temp("owner_name", "单思");
        ::setup();
}
