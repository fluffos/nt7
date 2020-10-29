// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m古小龙[2;37;0m[2;37;0m", ({"gulong"}));        
        set("gender", "男性");                
        set("long", "$HIC$古小龙[2;37;0m
它是古龙的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "auto");
        set("owner_name", "古龙");
        set_temp("owner", "auto");
        set_temp("owner_name", "古龙");
        ::setup();
}
