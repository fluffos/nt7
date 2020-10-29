// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老狗秘史[2;37;0m[2;37;0m", ({"lgms"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是老狗纳的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lgn");
        set("owner_name", "老狗纳");
        set_temp("owner", "lgn");
        set_temp("owner_name", "老狗纳");
        ::setup();
}
