// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("钱[2;37;0m[2;37;0m", ({"ooo"}));        
        set("gender", "女性");                
        set("long", "钱[2;37;0m
它是令狐不冲的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ckk");
        set("owner_name", "令狐不冲");
        set_temp("owner", "ckk");
        set_temp("owner_name", "令狐不冲");
        ::setup();
}
