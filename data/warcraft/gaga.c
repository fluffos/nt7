// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m杳[1;32m杳[2;37;0m[2;37;0m[2;37;0m", ({"yaoyao"}));        
        set("gender", "女性");                
        set("long", "$BLINK$$HIR$杳$HIG$杳$NOR$[2;37;0m
它是旮旮的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "gaga");
        set("owner_name", "旮旮");
        set_temp("owner", "gaga");
        set_temp("owner_name", "旮旮");
        ::setup();
}
