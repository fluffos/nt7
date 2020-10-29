// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("仓库车[2;37;0m[2;37;0m", ({"store"}));        
        set("gender", "男性");                
        set("long", "仓库车[2;37;0m
它是符石仓库的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "storetwo");
        set("owner_name", "符石仓库");
        set_temp("owner", "storetwo");
        set_temp("owner_name", "符石仓库");
        ::setup();
}
