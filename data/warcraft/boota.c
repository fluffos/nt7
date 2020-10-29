// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("再隔壁女孩[2;37;0m[2;37;0m", ({"bootalong"}));        
        set("gender", "男性");                
        set("long", "伙人[2;37;0m
它是隔壁老王的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "boota");
        set("owner_name", "隔壁老王");
        set_temp("owner", "boota");
        set_temp("owner_name", "隔壁老王");
        ::setup();
}
