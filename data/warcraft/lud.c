// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m摇钱树[2;37;0m[2;37;0m", ({"qlong"}));        
        set("gender", "男性");                
        set("long", "摇钱树[2;37;0m
它是采花四的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lud");
        set("owner_name", "采花四");
        set_temp("owner", "lud");
        set_temp("owner_name", "采花四");
        ::setup();
}
