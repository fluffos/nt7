// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m快进任务[2;37;0m[2;37;0m", ({"kjrw"}));        
        set("gender", "男性");                
        set("long", "提高速度[2;37;0m
它是右手食指的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ljjgm");
        set("owner_name", "右手食指");
        set_temp("owner", "ljjgm");
        set_temp("owner_name", "右手食指");
        ::setup();
}
