// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("怪兽[2;37;0m[2;37;0m", ({"kill"}));        
        set("gender", "女性");                
        set("long", "这是一只[2;37;0m
它是铁衣的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "riagny");
        set("owner_name", "铁衣");
        set_temp("owner", "riagny");
        set_temp("owner_name", "铁衣");
        ::setup();
}
