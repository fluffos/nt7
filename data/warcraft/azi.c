// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[33m拉土车[2;37;0m[2;37;0m", ({"azis"}));        
        set("gender", "男性");                
        set("long", "阿紫的坐骑[2;37;0m
它是阿紫的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "azi");
        set("owner_name", "阿紫");
        set_temp("owner", "azi");
        set_temp("owner_name", "阿紫");
        ::setup();
}
