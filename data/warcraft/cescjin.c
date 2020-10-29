// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("霖霖七[2;37;0m[2;37;0m", ({"oot"}));        
        set("gender", "女性");                
        set("long", "霖霖七[2;37;0m
它是暗煞的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "cescjin");
        set("owner_name", "暗煞");
        set_temp("owner", "cescjin");
        set_temp("owner_name", "暗煞");
        ::setup();
}
