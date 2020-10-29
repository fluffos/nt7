// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是库存乙的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "stockb");
        set("owner_name", "库存乙");
        set_temp("owner", "stockb");
        set_temp("owner_name", "库存乙");
        ::setup();
}
