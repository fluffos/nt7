// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m四海[1;37m游龙[2;37;0m[2;37;0m", ({"dragonx"}));        
        set("gender", "女性");                
        set("long", "一条龙[2;37;0m
它是有杀气的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "mks");
        set("owner_name", "有杀气");
        set_temp("owner", "mks");
        set_temp("owner_name", "有杀气");
        ::setup();
}
