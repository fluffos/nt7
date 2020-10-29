// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[33m拉土车[33m[2;37;0m[2;37;0m", ({"foxs"}));        
        set("gender", "男性");                
        set("long", "米米的坐骑[2;37;0m
它是米米的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fox");
        set("owner_name", "米米");
        set_temp("owner", "fox");
        set_temp("owner_name", "米米");
        ::setup();
}
