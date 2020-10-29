// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("高潮肾寒[2;37;0m[2;37;0m", ({"mylxer"}));        
        set("gender", "女性");                
        set("long", "高潮肾寒[2;37;0m
它是风林火山的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lxer");
        set("owner_name", "风林火山");
        set_temp("owner", "lxer");
        set_temp("owner_name", "风林火山");
        ::setup();
}
