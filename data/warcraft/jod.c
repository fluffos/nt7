// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"moue"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是鬼谷子的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jod");
        set("owner_name", "鬼谷子");
        set_temp("owner", "jod");
        set_temp("owner_name", "鬼谷子");
        ::setup();
}
