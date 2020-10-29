// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老狗耳顺[2;37;0m[2;37;0m", ({"lges"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是老狗伍的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lge");
        set("owner_name", "老狗伍");
        set_temp("owner", "lge");
        set_temp("owner_name", "老狗伍");
        ::setup();
}
