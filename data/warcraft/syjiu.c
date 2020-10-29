// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("马儿快跑[2;37;0m[2;37;0m", ({"qimaer"}));        
        set("gender", "女性");                
        set("long", "马儿快跑[2;37;0m
它是太刀血的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "syjiu");
        set("owner_name", "太刀血");
        set_temp("owner", "syjiu");
        set_temp("owner_name", "太刀血");
        ::setup();
}
