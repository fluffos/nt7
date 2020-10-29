// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("蠢子派肥鸡[2;37;0m[2;37;0m", ({"kingsly"}));        
        set("gender", "男性");                
        set("long", "肥不是亮点，肥而飞的起才是亮点！！！[2;37;0m
它是灭世天命的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "slefuod");
        set("owner_name", "灭世天命");
        set_temp("owner", "slefuod");
        set_temp("owner_name", "灭世天命");
        ::setup();
}
