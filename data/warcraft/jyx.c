// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("猪猪[2;37;0m[2;37;0m", ({"zhuzhu"}));        
        set("gender", "女性");                
        set("long", "猪[2;37;0m
它是剑影邪的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "jyx");
        set("owner_name", "剑影邪");
        set_temp("owner", "jyx");
        set_temp("owner_name", "剑影邪");
        ::setup();
}
