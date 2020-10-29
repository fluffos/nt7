// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("宝马[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "奔驰开来了[2;37;0m
它是单三的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "sanc");
        set("owner_name", "单三");
        set_temp("owner", "sanc");
        set_temp("owner_name", "单三");
        ::setup();
}
