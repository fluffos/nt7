// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m杲[1;32m杳[2;37;0m[2;37;0m[2;37;0m", ({"gaoyao"}));        
        set("gender", "女性");                
        set("long", "$BLINK$$HIR$杲$HIG$杳$NOR$[2;37;0m
它是旯旮的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "laga");
        set("owner_name", "旯旮");
        set_temp("owner", "laga");
        set_temp("owner_name", "旯旮");
        ::setup();
}
