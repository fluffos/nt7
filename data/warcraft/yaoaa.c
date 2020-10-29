// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("哎哎[2;37;0m[2;37;0m", ({"yaoaaa"}));        
        set("gender", "男性");                
        set("long", "哎哎[2;37;0m
它是药哎哎的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yaoaa");
        set("owner_name", "药哎哎");
        set_temp("owner", "yaoaa");
        set_temp("owner_name", "药哎哎");
        ::setup();
}
