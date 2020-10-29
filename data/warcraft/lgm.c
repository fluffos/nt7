// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老狗没事[2;37;0m[2;37;0m", ({"lgms"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是老狗毛的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lgm");
        set("owner_name", "老狗毛");
        set_temp("owner", "lgm");
        set_temp("owner_name", "老狗毛");
        ::setup();
}
