// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"dsy"}));        
        set("gender", "女性");                
        set("long", "这是一只白虎[2;37;0m
它是船长的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "dsydxla");
        set("owner_name", "船长");
        set_temp("owner", "dsydxla");
        set_temp("owner_name", "船长");
        ::setup();
}
