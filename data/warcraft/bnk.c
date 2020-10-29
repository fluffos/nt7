// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m道风翩翩[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "$HIC$道风翩翩[2;37;0m
它是疯欧阳的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "bnk");
        set("owner_name", "疯欧阳");
        set_temp("owner", "bnk");
        set_temp("owner_name", "疯欧阳");
        ::setup();
}
