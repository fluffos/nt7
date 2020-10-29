// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老狗发烧[2;37;0m[2;37;0m", ({"lgfs"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是老狗陆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lgf");
        set("owner_name", "老狗陆");
        set_temp("owner", "lgf");
        set_temp("owner_name", "老狗陆");
        ::setup();
}
