// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小竹签[2;37;0m[2;37;0m", ({"xiaoju"}));        
        set("gender", "男性");                
        set("long", "魔幻兽[2;37;0m
它是炼阿的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lda");
        set("owner_name", "炼阿");
        set_temp("owner", "lda");
        set_temp("owner_name", "炼阿");
        ::setup();
}
