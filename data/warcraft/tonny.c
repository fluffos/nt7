// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("狗逼[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "狗[2;37;0m
它是艹西的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "tonny");
        set("owner_name", "艹西");
        set_temp("owner", "tonny");
        set_temp("owner_name", "艹西");
        ::setup();
}
