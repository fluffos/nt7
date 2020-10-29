// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("冰鸟[2;37;0m[2;37;0m", ({"phoenix"}));        
        set("gender", "女性");                
        set("long", "冰鸟[2;37;0m
它是阳焰的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "frey");
        set("owner_name", "阳焰");
        set_temp("owner", "frey");
        set_temp("owner_name", "阳焰");
        ::setup();
}
