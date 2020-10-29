// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m洛神鸟[2;37;0m[2;37;0m", ({"doo"}));        
        set("gender", "男性");                
        set("long", "坐骑[2;37;0m
它是齐洛仙的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "shar");
        set("owner_name", "齐洛仙");
        set_temp("owner", "shar");
        set_temp("owner_name", "齐洛仙");
        ::setup();
}
