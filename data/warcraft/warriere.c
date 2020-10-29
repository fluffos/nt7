// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m黄金比蒙[2;37;0m[2;37;0m", ({"bimeng"}));        
        set("gender", "男性");                
        set("long", "超级圣兽，无与伦比[2;37;0m
它是暗器的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "warriere");
        set("owner_name", "暗器");
        set_temp("owner", "warriere");
        set_temp("owner_name", "暗器");
        ::setup();
}
