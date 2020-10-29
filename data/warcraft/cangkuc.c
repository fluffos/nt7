// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("甲拖车[2;37;0m[2;37;0m", ({"tttc"}));        
        set("gender", "男性");                
        set("long", "甲拖车[2;37;0m
它是甲仓库的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "cangkuc");
        set("owner_name", "甲仓库");
        set_temp("owner", "cangkuc");
        set_temp("owner_name", "甲仓库");
        ::setup();
}
