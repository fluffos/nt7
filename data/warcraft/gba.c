// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m挥[31m尽[1;32m赵[34m云[1;33m[2;37;0m[2;37;0m", ({"wolf"}));        
        set("gender", "男性");                
        set("long", "王王[2;37;0m
它是洪二公的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "gba");
        set("owner_name", "洪二公");
        set_temp("owner", "gba");
        set_temp("owner_name", "洪二公");
        ::setup();
}
