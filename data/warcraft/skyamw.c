// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("筋斗云[2;37;0m[2;37;0m", ({"jdy"}));        
        set("gender", "男性");                
        set("long", "筋斗云[2;37;0m
它是旧梦难温的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "skyamw");
        set("owner_name", "旧梦难温");
        set_temp("owner", "skyamw");
        set_temp("owner_name", "旧梦难温");
        ::setup();
}
