// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("什么呢[2;37;0m[2;37;0m", ({"newly"}));        
        set("gender", "女性");                
        set("long", "什么呢[2;37;0m
它是新手的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "newa");
        set("owner_name", "新手");
        set_temp("owner", "newa");
        set_temp("owner_name", "新手");
        ::setup();
}
