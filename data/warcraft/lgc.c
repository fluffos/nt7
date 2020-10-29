// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老狗传说[2;37;0m[2;37;0m", ({"lgcs"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是老狗叁的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lgc");
        set("owner_name", "老狗叁");
        set_temp("owner", "lgc");
        set_temp("owner_name", "老狗叁");
        ::setup();
}
