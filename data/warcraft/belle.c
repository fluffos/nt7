// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("雀儿[2;37;0m[2;37;0m", ({"elle"}));        
        set("gender", "男性");                
        set("long", "雄[2;37;0m
它是灵水的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "belle");
        set("owner_name", "灵水");
        set_temp("owner", "belle");
        set_temp("owner_name", "灵水");
        ::setup();
}
