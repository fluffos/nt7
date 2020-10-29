// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m痘痘龙[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "痘痘龙[2;37;0m
它是寂天使的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "vvv");
        set("owner_name", "寂天使");
        set_temp("owner", "vvv");
        set_temp("owner_name", "寂天使");
        ::setup();
}
