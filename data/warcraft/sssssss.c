// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m玛莎拉蒂[2;37;0m[2;37;0m", ({"dama"}));        
        set("gender", "男性");                
        set("long", "玛莎拉蒂[2;37;0m
它是金牙的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "sssssss");
        set("owner_name", "金牙");
        set_temp("owner", "sssssss");
        set_temp("owner_name", "金牙");
        ::setup();
}
