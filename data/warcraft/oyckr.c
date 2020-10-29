// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m擎天柱[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "男性");                
        set("long", "$HIC$擎天柱[2;37;0m
它是欧阳楚的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "oyckr");
        set("owner_name", "欧阳楚");
        set_temp("owner", "oyckr");
        set_temp("owner_name", "欧阳楚");
        ::setup();
}
