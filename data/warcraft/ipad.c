// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m妖兽[2;37;0m[2;37;0m", ({"sss"}));        
        set("gender", "男性");                
        set("long", "妖惑众生[2;37;0m
它是苹果的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ipad");
        set("owner_name", "苹果");
        set_temp("owner", "ipad");
        set_temp("owner_name", "苹果");
        ::setup();
}
