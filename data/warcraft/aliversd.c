// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m鱼香肉丝[2;37;0m[2;37;0m", ({"pesib"}));        
        set("gender", "男性");                
        set("long", "鱼香肉丝[2;37;0m
它是阿尔死的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "aliversd");
        set("owner_name", "阿尔死");
        set_temp("owner", "aliversd");
        set_temp("owner_name", "阿尔死");
        ::setup();
}
