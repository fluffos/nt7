// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m最[1;32m贱[2;37;0m[2;37;0m", ({"tooly"}));        
        set("gender", "男性");                
        set("long", "最贱[2;37;0m
它是看看的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "jiangzcan");
        set("owner_name", "看看");
        set_temp("owner", "jiangzcan");
        set_temp("owner_name", "看看");
        ::setup();
}
