// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老狗[2;37;0m[2;37;0m", ({"lghs"}));        
        set("gender", "男性");                
        set("long", "好色[2;37;0m
它是老狗捌的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lgh");
        set("owner_name", "老狗捌");
        set_temp("owner", "lgh");
        set_temp("owner_name", "老狗捌");
        ::setup();
}
