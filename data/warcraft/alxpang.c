// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("哈哈[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是风四郎的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "alxpang");
        set("owner_name", "风四郎");
        set_temp("owner", "alxpang");
        set_temp("owner_name", "风四郎");
        ::setup();
}
