// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("河内蛟龙[2;37;0m[2;37;0m", ({"huansl"}));        
        set("gender", "女性");                
        set("long", "河内蛟龙[2;37;0m
它是有条小河的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xiaohe");
        set("owner_name", "有条小河");
        set_temp("owner", "xiaohe");
        set_temp("owner_name", "有条小河");
        ::setup();
}
