// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;32m滴答[2;37;0m[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "$BLINK$$HIG$滴答$NOR$[2;37;0m
它是滴滴答答的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "tick");
        set("owner_name", "滴滴答答");
        set_temp("owner", "tick");
        set_temp("owner_name", "滴滴答答");
        ::setup();
}
