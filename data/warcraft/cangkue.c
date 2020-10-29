// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小溜溜[2;37;0m[2;37;0m", ({"xll"}));        
        set("gender", "女性");                
        set("long", "小溜溜[2;37;0m
它是腕仓库的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "cangkue");
        set("owner_name", "腕仓库");
        set_temp("owner", "cangkue");
        set_temp("owner_name", "腕仓库");
        ::setup();
}
