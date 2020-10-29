// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m劫数[2;37;0m[2;37;0m", ({"jie"}));        
        set("gender", "男性");                
        set("long", "劫数难逃。[2;37;0m
它是渡情天的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "jojosl");
        set("owner_name", "渡情天");
        set_temp("owner", "jojosl");
        set_temp("owner_name", "渡情天");
        ::setup();
}
