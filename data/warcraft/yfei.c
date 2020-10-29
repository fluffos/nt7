// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;34m乌云[1;37m盖雪[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这匹神驹通体雪白，只是马背黑色如云，追风逐电、神骏非常。[2;37;0m
它是岳飞的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yfei");
        set("owner_name", "岳飞");
        set_temp("owner", "yfei");
        set_temp("owner_name", "岳飞");
        ::setup();
}
