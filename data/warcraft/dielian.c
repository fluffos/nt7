// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "女性");                
        set("long", "朱雀[2;37;0m
它是恋蝶的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dielian");
        set("owner_name", "恋蝶");
        set_temp("owner", "dielian");
        set_temp("owner_name", "恋蝶");
        ::setup();
}
