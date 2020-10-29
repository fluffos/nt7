// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老狗都是[2;37;0m[2;37;0m", ({"lgds"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是老狗肆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lgd");
        set("owner_name", "老狗肆");
        set_temp("owner", "lgd");
        set_temp("owner_name", "老狗肆");
        ::setup();
}
