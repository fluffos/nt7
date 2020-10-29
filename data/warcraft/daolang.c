// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m刀狼[2;37;0m[2;37;0m", ({"lang"}));        
        set("gender", "男性");                
        set("long", "$BLINK$$HIR$刀狼的$HIC$宠物[2;37;0m
它是刀郎的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "daolang");
        set("owner_name", "刀郎");
        set_temp("owner", "daolang");
        set_temp("owner_name", "刀郎");
        ::setup();
}
