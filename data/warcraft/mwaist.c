// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m制式巨龙[2;37;0m[2;37;0m", ({"mwaist_dragon"}));        
        set("gender", "男性");                
        set("long", "一头军用制式巨龙。[2;37;0m
它是腰带仓库的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "mwaist");
        set("owner_name", "腰带仓库");
        set_temp("owner", "mwaist");
        set_temp("owner_name", "腰带仓库");
        ::setup();
}
