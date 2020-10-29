// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m杳[1;32m杲[2;37;0m[2;37;0m[2;37;0m", ({"yaogao"}));        
        set("gender", "女性");                
        set("long", "$BLINK$$HIR$杳$HIG$杲$NOR$[2;37;0m
它是旮旯的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "gala");
        set("owner_name", "旮旯");
        set_temp("owner", "gala");
        set_temp("owner_name", "旮旯");
        ::setup();
}
