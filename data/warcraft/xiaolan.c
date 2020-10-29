// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白云[2;37;0m[2;37;0m", ({"baiyun"}));        
        set("gender", "女性");                
        set("long", "飘浮天空的浮云[2;37;0m
它是小兰的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xiaolan");
        set("owner_name", "小兰");
        set_temp("owner", "xiaolan");
        set_temp("owner_name", "小兰");
        ::setup();
}
