// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("金龙[2;37;0m[2;37;0m", ({"jmlong"}));        
        set("gender", "男性");                
        set("long", "金皿的龙 [2;37;0m
它是金皿的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "jinmin");
        set("owner_name", "金皿");
        set_temp("owner", "jinmin");
        set_temp("owner_name", "金皿");
        ::setup();
}
