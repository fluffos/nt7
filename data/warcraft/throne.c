// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m斯巴达克斯[2;37;0m[2;37;0m", ({"spartacus"}));        
        set("gender", "男性");                
        set("long", "斯巴达克斯[2;37;0m
它是权利游戏的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "throne");
        set("owner_name", "权利游戏");
        set_temp("owner", "throne");
        set_temp("owner_name", "权利游戏");
        ::setup();
}
