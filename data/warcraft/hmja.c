// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小猪笼[2;37;0m[2;37;0m", ({"hmjaq"}));        
        set("gender", "男性");                
        set("long", "猪一只[2;37;0m
它是当小鬼的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "hmja");
        set("owner_name", "当小鬼");
        set_temp("owner", "hmja");
        set_temp("owner_name", "当小鬼");
        ::setup();
}
