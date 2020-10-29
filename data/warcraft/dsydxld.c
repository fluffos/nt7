// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"dsy"}));        
        set("gender", "男性");                
        set("long", "玄武[2;37;0m
它是随便挂着的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "dsydxld");
        set("owner_name", "随便挂着");
        set_temp("owner", "dsydxld");
        set_temp("owner_name", "随便挂着");
        ::setup();
}
