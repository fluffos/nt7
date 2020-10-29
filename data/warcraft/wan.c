// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m甲魔[2;37;0m[2;37;0m", ({"jiajiajia"}));        
        set("gender", "男性");                
        set("long", "$HIR$甲魔[2;37;0m
它是魔晚的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wan");
        set("owner_name", "魔晚");
        set_temp("owner", "wan");
        set_temp("owner_name", "魔晚");
        ::setup();
}
