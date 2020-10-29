// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("冰鸟[2;37;0m[2;37;0m", ({"phoenix"}));        
        set("gender", "男性");                
        set("long", "冰鸟[2;37;0m
它是影月的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "freya");
        set("owner_name", "影月");
        set_temp("owner", "freya");
        set_temp("owner_name", "影月");
        ::setup();
}
