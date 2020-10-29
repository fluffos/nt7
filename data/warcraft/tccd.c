// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("马四[2;37;0m[2;37;0m", ({"tccab"}));        
        set("gender", "男性");                
        set("long", "马四[2;37;0m
它是偷四的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tccd");
        set("owner_name", "偷四");
        set_temp("owner", "tccd");
        set_temp("owner_name", "偷四");
        ::setup();
}
