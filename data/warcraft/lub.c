// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m摇钱树[2;37;0m[2;37;0m", ({"qlong"}));        
        set("gender", "男性");                
        set("long", "摇钱树[2;37;0m
它是采花二的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lub");
        set("owner_name", "采花二");
        set_temp("owner", "lub");
        set_temp("owner_name", "采花二");
        ::setup();
}
