// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m绝情兽[2;37;0m[2;37;0m", ({"doo"}));        
        set("gender", "男性");                
        set("long", "坐骑[2;37;0m
它是林若音的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "shak");
        set("owner_name", "林若音");
        set_temp("owner", "shak");
        set_temp("owner_name", "林若音");
        ::setup();
}
