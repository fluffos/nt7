// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m暗帝圣龙[2;37;0m[2;37;0m", ({"edragon"}));        
        set("gender", "男性");                
        set("long", "一条龙[2;37;0m
它是鲁啦啦的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "naked");
        set("owner_name", "鲁啦啦");
        set_temp("owner", "naked");
        set_temp("owner_name", "鲁啦啦");
        ::setup();
}
