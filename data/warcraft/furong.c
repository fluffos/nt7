// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m瘸腿老叫驴[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这头老叫驴又老又丑，浑身斑癣，芙蓉姐姐的性工具。[2;37;0m
它是芙蓉姐姐的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "furong");
        set("owner_name", "芙蓉姐姐");
        set_temp("owner", "furong");
        set_temp("owner_name", "芙蓉姐姐");
        ::setup();
}
