// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("仙鹤[2;37;0m[2;37;0m", ({"xianhe"}));        
        set("gender", "男性");                
        set("long", "一只雪白的仙鹤，自由的飞翔[2;37;0m
它是萱鸸的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xuaner");
        set("owner_name", "萱鸸");
        set_temp("owner", "xuaner");
        set_temp("owner_name", "萱鸸");
        ::setup();
}
