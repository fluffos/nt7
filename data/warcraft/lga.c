// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老狗爱死[2;37;0m[2;37;0m", ({"lgas"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是老狗壹的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lga");
        set("owner_name", "老狗壹");
        set_temp("owner", "lga");
        set_temp("owner_name", "老狗壹");
        ::setup();
}
