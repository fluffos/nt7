// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("菜[2;37;0m[2;37;0m", ({"bbbtx"}));        
        set("gender", "女性");                
        set("long", "菜[2;37;0m
它是偷采吧的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "txb");
        set("owner_name", "偷采吧");
        set_temp("owner", "txb");
        set_temp("owner_name", "偷采吧");
        ::setup();
}
