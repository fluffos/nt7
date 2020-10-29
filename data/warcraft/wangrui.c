// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("爱骑[2;37;0m[2;37;0m", ({"ilovelong"}));        
        set("gender", "男性");                
        set("long", "爱骑[2;37;0m
它是王瑞的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wangrui");
        set("owner_name", "王瑞");
        set_temp("owner", "wangrui");
        set_temp("owner_name", "王瑞");
        ::setup();
}
