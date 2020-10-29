// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m金蛇[2;37;0m[2;37;0m", ({"kgs"}));        
        set("gender", "男性");                
        set("long", "金蛇[2;37;0m
它是夏雪宜的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xia");
        set("owner_name", "夏雪宜");
        set_temp("owner", "xia");
        set_temp("owner_name", "夏雪宜");
        ::setup();
}
