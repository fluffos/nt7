// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("兔兔[2;37;0m[2;37;0m", ({"tutu"}));        
        set("gender", "男性");                
        set("long", "这是一只可爱的小白兔[2;37;0m
它是风千越的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "uniax");
        set("owner_name", "风千越");
        set_temp("owner", "uniax");
        set_temp("owner_name", "风千越");
        ::setup();
}
