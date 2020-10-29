// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("血麒麟[2;37;0m[2;37;0m", ({"fyy"}));        
        set("gender", "男性");                
        set("long", "血麒麟[2;37;0m
它是天涯浪子的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "fyahh");
        set("owner_name", "天涯浪子");
        set_temp("owner", "fyahh");
        set_temp("owner_name", "天涯浪子");
        ::setup();
}
