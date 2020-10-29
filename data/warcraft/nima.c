// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("你大爷[2;37;0m[2;37;0m", ({"nill"}));        
        set("gender", "男性");                
        set("long", "$HIC$你大爷[2;37;0m
它是尼玛的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "nima");
        set("owner_name", "尼玛");
        set_temp("owner", "nima");
        set_temp("owner_name", "尼玛");
        ::setup();
}
