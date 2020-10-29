// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火鸟[2;37;0m[2;37;0m", ({"huoniao"}));        
        set("gender", "男性");                
        set("long", "火鸟[2;37;0m
它是风霜的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fengshuang");
        set("owner_name", "风霜");
        set_temp("owner", "fengshuang");
        set_temp("owner_name", "风霜");
        ::setup();
}
