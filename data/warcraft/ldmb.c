// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("猪雀[2;37;0m[2;37;0m", ({"zqqqq"}));        
        set("gender", "女性");                
        set("long", "猪[2;37;0m
它是连丹的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ldmb");
        set("owner_name", "连丹");
        set_temp("owner", "ldmb");
        set_temp("owner_name", "连丹");
        ::setup();
}
