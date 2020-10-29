// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小丸子[2;37;0m[2;37;0m", ({"moono"}));        
        set("gender", "男性");                
        set("long", "no[2;37;0m
它是妄月眠的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "reaki");
        set("owner_name", "妄月眠");
        set_temp("owner", "reaki");
        set_temp("owner_name", "妄月眠");
        ::setup();
}
