// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("丽丽[2;37;0m[2;37;0m", ({"leilei"}));        
        set("gender", "男性");                
        set("long", "一只朱雀[2;37;0m
它是段昱的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "orion");
        set("owner_name", "段昱");
        set_temp("owner", "orion");
        set_temp("owner_name", "段昱");
        ::setup();
}
