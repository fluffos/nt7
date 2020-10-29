// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("猪雀[2;37;0m[2;37;0m", ({"zqqqq"}));        
        set("gender", "女性");                
        set("long", "猪[2;37;0m
它是怜丹的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ldmf");
        set("owner_name", "怜丹");
        set_temp("owner", "ldmf");
        set_temp("owner_name", "怜丹");
        ::setup();
}
