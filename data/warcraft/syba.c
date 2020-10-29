// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("腰带[2;37;0m[2;37;0m", ({"yaodei"}));        
        set("gender", "女性");                
        set("long", "腰带[2;37;0m
它是药太极的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "syba");
        set("owner_name", "药太极");
        set_temp("owner", "syba");
        set_temp("owner_name", "药太极");
        ::setup();
}
