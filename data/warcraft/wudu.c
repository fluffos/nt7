// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("香香公主[2;37;0m[2;37;0m", ({"wudulong"}));        
        set("gender", "女性");                
        set("long", "执行[2;37;0m
它是降头师的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wudu");
        set("owner_name", "降头师");
        set_temp("owner", "wudu");
        set_temp("owner_name", "降头师");
        ::setup();
}
