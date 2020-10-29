// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m剑心通明[2;37;0m[2;37;0m", ({"qiwan"}));        
        set("gender", "男性");                
        set("long", "通明！[2;37;0m
它是七剑下天的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dangqi");
        set("owner_name", "七剑下天");
        set_temp("owner", "dangqi");
        set_temp("owner_name", "七剑下天");
        ::setup();
}
