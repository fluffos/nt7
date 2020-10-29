// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[33m黄金[2;37;0m[2;37;0m", ({"gold"}));        
        set("gender", "男性");                
        set("long", "移动的黄金 宝石 材料仓库[2;37;0m
它是齐火的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "bapll");
        set("owner_name", "齐火");
        set_temp("owner", "bapll");
        set_temp("owner_name", "齐火");
        ::setup();
}
