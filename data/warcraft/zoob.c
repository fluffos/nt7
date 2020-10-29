// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("虎鞭[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "虎鞭[2;37;0m
它是生肖虎的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zoob");
        set("owner_name", "生肖虎");
        set_temp("owner", "zoob");
        set_temp("owner_name", "生肖虎");
        ::setup();
}
