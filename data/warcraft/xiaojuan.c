// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qlong"}));        
        set("gender", "男性");                
        set("long", "傻里傻气的青龙，估计跑的还挺快的[2;37;0m
它是龙四龙的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xiaojuan");
        set("owner_name", "龙四龙");
        set_temp("owner", "xiaojuan");
        set_temp("owner_name", "龙四龙");
        ::setup();
}
