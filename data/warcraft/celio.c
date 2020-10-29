// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m黄金圣龙[2;37;0m[2;37;0m", ({"shenglong"}));        
        set("gender", "男性");                
        set("long", "一直浑身散发着阵阵龙威的圣龙。[2;37;0m
它是独孤木木的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "celio");
        set("owner_name", "独孤木木");
        set_temp("owner", "celio");
        set_temp("owner_name", "独孤木木");
        ::setup();
}
