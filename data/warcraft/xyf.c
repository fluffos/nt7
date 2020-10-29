// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("追月[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "女性");                
        set("long", "追月 $HIC$[2;37;0m
它是冷如霜的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xyf");
        set("owner_name", "冷如霜");
        set_temp("owner", "xyf");
        set_temp("owner_name", "冷如霜");
        ::setup();
}
