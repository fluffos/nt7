// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("噗噗[2;37;0m[2;37;0m", ({"pupu"}));        
        set("gender", "男性");                
        set("long", "噗噗[2;37;0m
它是布丁的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "pudding");
        set("owner_name", "布丁");
        set_temp("owner", "pudding");
        set_temp("owner_name", "布丁");
        ::setup();
}
