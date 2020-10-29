// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m筋斗云[2;37;0m[2;37;0m", ({"xql"}));        
        set("gender", "男性");                
        set("long", "一朵筋斗云[2;37;0m
它是年华似水的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ching");
        set("owner_name", "年华似水");
        set_temp("owner", "ching");
        set_temp("owner_name", "年华似水");
        ::setup();
}
