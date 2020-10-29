// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青青青青青龙[2;37;0m[2;37;0m", ({"xiee"}));        
        set("gender", "男性");                
        set("long", "一条青龙[2;37;0m
它是伯赏坤瑜的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "scdyxiee");
        set("owner_name", "伯赏坤瑜");
        set_temp("owner", "scdyxiee");
        set_temp("owner_name", "伯赏坤瑜");
        ::setup();
}
