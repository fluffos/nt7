// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大哥[2;37;0m[2;37;0m", ({"girlioi"}));        
        set("gender", "男性");                
        set("long", "大哥[2;37;0m
它是逃汰郎的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "taoo");
        set("owner_name", "逃汰郎");
        set_temp("owner", "taoo");
        set_temp("owner_name", "逃汰郎");
        ::setup();
}
