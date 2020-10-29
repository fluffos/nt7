// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白马[2;37;0m[2;37;0m", ({"booo"}));        
        set("gender", "女性");                
        set("long", "$HIW$白马[2;37;0m
它是莉聆的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zzvv");
        set("owner_name", "莉聆");
        set_temp("owner", "zzvv");
        set_temp("owner_name", "莉聆");
        ::setup();
}
