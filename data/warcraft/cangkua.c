// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("头拖车[2;37;0m[2;37;0m", ({"ttta"}));        
        set("gender", "男性");                
        set("long", "头拖车[2;37;0m
它是头仓库的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "cangkua");
        set("owner_name", "头仓库");
        set_temp("owner", "cangkua");
        set_temp("owner_name", "头仓库");
        ::setup();
}
