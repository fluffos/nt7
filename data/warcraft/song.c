// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("顺路快递[2;37;0m[2;37;0m", ({"benz"}));        
        set("gender", "男性");                
        set("long", "          [2;37;0m
它是宋江的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "song");
        set("owner_name", "宋江");
        set_temp("owner", "song");
        set_temp("owner_name", "宋江");
        ::setup();
}
