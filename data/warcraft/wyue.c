// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("鱼雀[2;37;0m[2;37;0m", ({"huoo"}));        
        set("gender", "女性");                
        set("long", "鱼雀[2;37;0m
它是西山无月的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wyue");
        set("owner_name", "西山无月");
        set_temp("owner", "wyue");
        set_temp("owner_name", "西山无月");
        ::setup();
}
