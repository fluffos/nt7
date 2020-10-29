// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m八岐大蛇[2;37;0m[2;37;0m", ({"sheba"}));        
        set("gender", "男性");                
        set("long", "九头蛇的二表哥！[2;37;0m
它是八仙过海的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dangba");
        set("owner_name", "八仙过海");
        set_temp("owner", "dangba");
        set_temp("owner_name", "八仙过海");
        ::setup();
}
