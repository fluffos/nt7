// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("三号[2;37;0m[2;37;0m", ({"cafe"}));        
        set("gender", "男性");                
        set("long", "三号[2;37;0m
它是咖啡三号的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ccfpaper");
        set("owner_name", "咖啡三号");
        set_temp("owner", "ccfpaper");
        set_temp("owner_name", "咖啡三号");
        ::setup();
}
