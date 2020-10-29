// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("异形[2;37;0m[2;37;0m", ({"dna"}));        
        set("gender", "男性");                
        set("long", "逆种[2;37;0m
它是二长的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "shitweekb");
        set("owner_name", "二长");
        set_temp("owner", "shitweekb");
        set_temp("owner_name", "二长");
        ::setup();
}
