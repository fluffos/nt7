// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("没美眉[2;37;0m[2;37;0m", ({"miao"}));        
        set("gender", "男性");                
        set("long", "嗷嗷嗷[2;37;0m
它是把妹玩的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "bmw");
        set("owner_name", "把妹玩");
        set_temp("owner", "bmw");
        set_temp("owner_name", "把妹玩");
        ::setup();
}
