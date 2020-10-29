// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小红[2;37;0m[2;37;0m", ({"save"}));        
        set("gender", "女性");                
        set("long", "小红[2;37;0m
它是太极蛋的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "olo");
        set("owner_name", "太极蛋");
        set_temp("owner", "olo");
        set_temp("owner_name", "太极蛋");
        ::setup();
}
