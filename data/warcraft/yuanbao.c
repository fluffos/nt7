// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白马[2;37;0m[2;37;0m", ({"myhorse"}));        
        set("gender", "男性");                
        set("long", "白马[2;37;0m
它是挖宝甲的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yuanbao");
        set("owner_name", "挖宝甲");
        set_temp("owner", "yuanbao");
        set_temp("owner_name", "挖宝甲");
        ::setup();
}
