// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m法号乱来[2;37;0m[2;37;0m", ({"pigaa"}));        
        set("gender", "男性");                
        set("long", "法号乱来,大家一起乱来吧。。[2;37;0m
它是胡搞瞎搞的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "piga");
        set("owner_name", "胡搞瞎搞");
        set_temp("owner", "piga");
        set_temp("owner_name", "胡搞瞎搞");
        ::setup();
}
