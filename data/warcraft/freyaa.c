// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("冰鸟[2;37;0m[2;37;0m", ({"phoenix"}));        
        set("gender", "男性");                
        set("long", "冰鸟[2;37;0m
它是思远的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "freyaa");
        set("owner_name", "思远");
        set_temp("owner", "freyaa");
        set_temp("owner_name", "思远");
        ::setup();
}
