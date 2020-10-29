// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m驴[1;33m车[2;37;0m[2;37;0m", ({"lvche"}));        
        set("gender", "男性");                
        set("long", "这是长工们的坐骑[2;37;0m
它是长工丙的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "thzc");
        set("owner_name", "长工丙");
        set_temp("owner", "thzc");
        set_temp("owner_name", "长工丙");
        ::setup();
}
