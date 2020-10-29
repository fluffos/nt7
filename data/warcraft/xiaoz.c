// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m瘸腿老叫驴[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "女性");                
        set("long", "这头老叫驴又老又丑，浑身斑癣，芙蓉姐姐的性工具。[2;37;0m
它是赵本山的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xiaoz");
        set("owner_name", "赵本山");
        set_temp("owner", "xiaoz");
        set_temp("owner_name", "赵本山");
        ::setup();
}
