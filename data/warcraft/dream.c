// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "                     [2;37;0m
它是梦遗的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dream");
        set("owner_name", "梦遗");
        set_temp("owner", "dream");
        set_temp("owner_name", "梦遗");
        ::setup();
}
