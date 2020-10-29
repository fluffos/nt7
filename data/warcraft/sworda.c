// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("我们辚[2;37;0m[2;37;0m", ({"swordalong"}));        
        set("gender", "男性");                
        set("long", "我们辚[2;37;0m
它是剑世界的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "sworda");
        set("owner_name", "剑世界");
        set_temp("owner", "sworda");
        set_temp("owner_name", "剑世界");
        ::setup();
}
