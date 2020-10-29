// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("剑鞘[2;37;0m[2;37;0m", ({"baoma"}));        
        set("gender", "男性");                
        set("long", "剑鞘[2;37;0m
它是剑九孤独的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "jjguiji");
        set("owner_name", "剑九孤独");
        set_temp("owner", "jjguiji");
        set_temp("owner_name", "剑九孤独");
        ::setup();
}
