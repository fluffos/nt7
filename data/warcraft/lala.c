// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m杲[1;32m杲[2;37;0m[2;37;0m[2;37;0m", ({"gaogao"}));        
        set("gender", "女性");                
        set("long", "$BLINK$$HIR$杲$HIG$杲$NOR$[2;37;0m
它是旯旯的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lala");
        set("owner_name", "旯旯");
        set_temp("owner", "lala");
        set_temp("owner_name", "旯旯");
        ::setup();
}
