// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("外套[2;37;0m[2;37;0m", ({"mygift"}));        
        set("gender", "女性");                
        set("long", "外套[2;37;0m
它是玛驰的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "much");
        set("owner_name", "玛驰");
        set_temp("owner", "much");
        set_temp("owner_name", "玛驰");
        ::setup();
}
