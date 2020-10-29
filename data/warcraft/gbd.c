// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("说不得[2;37;0m[2;37;0m", ({"gbdlong"}));        
        set("gender", "男性");                
        set("long", "数额[2;37;0m
它是顾不得的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "gbd");
        set("owner_name", "顾不得");
        set_temp("owner", "gbd");
        set_temp("owner_name", "顾不得");
        ::setup();
}
