// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("东北[2;37;0m[2;37;0m", ({"oko"}));        
        set("gender", "男性");                
        set("long", "纯种东北虎[2;37;0m
它是天天的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yhhdl");
        set("owner_name", "天天");
        set_temp("owner", "yhhdl");
        set_temp("owner_name", "天天");
        ::setup();
}
