// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老狗看守[2;37;0m[2;37;0m", ({"lgks"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是老狗依依的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lgk");
        set("owner_name", "老狗依依");
        set_temp("owner", "lgk");
        set_temp("owner_name", "老狗依依");
        ::setup();
}
