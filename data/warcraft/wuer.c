// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "睡袋[2;37;0m
它是武二郎的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wuer");
        set("owner_name", "武二郎");
        set_temp("owner", "wuer");
        set_temp("owner_name", "武二郎");
        ::setup();
}
