// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("拜纳姆[2;37;0m[2;37;0m", ({"bnm"}));        
        set("gender", "男性");                
        set("long", "finish[2;37;0m
它是周丹贰的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "btb");
        set("owner_name", "周丹贰");
        set_temp("owner", "btb");
        set_temp("owner_name", "周丹贰");
        ::setup();
}
