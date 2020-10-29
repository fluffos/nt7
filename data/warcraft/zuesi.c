// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("哈哈[2;37;0m[2;37;0m", ({"sleep_bag"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是九号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zuesi");
        set("owner_name", "九号");
        set_temp("owner", "zuesi");
        set_temp("owner_name", "九号");
        ::setup();
}
