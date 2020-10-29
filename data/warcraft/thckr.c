// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m风扫落叶[2;37;0m[2;37;0m", ({"haichao"}));        
        set("gender", "男性");                
        set("long", "$HIC$风扫落叶[2;37;0m
它是楚萧的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "thckr");
        set("owner_name", "楚萧");
        set_temp("owner", "thckr");
        set_temp("owner_name", "楚萧");
        ::setup();
}
