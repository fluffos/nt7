// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("哦我饿哦[2;37;0m[2;37;0m", ({"oiowe"}));        
        set("gender", "男性");                
        set("long", "哦我饿哦[2;37;0m
它是苍狼的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "feel");
        set("owner_name", "苍狼");
        set_temp("owner", "feel");
        set_temp("owner_name", "苍狼");
        ::setup();
}
