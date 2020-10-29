// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("母鸡[2;37;0m[2;37;0m", ({"dft"}));        
        set("gender", "男性");                
        set("long", "母鸡[2;37;0m
它是欧阳四的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dgd");
        set("owner_name", "欧阳四");
        set_temp("owner", "dgd");
        set_temp("owner_name", "欧阳四");
        ::setup();
}
