// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("一座山脉[2;37;0m[2;37;0m", ({"iceshan"}));        
        set("gender", "女性");                
        set("long", "会动的冰山[2;37;0m
它是冷如冰的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "rubing");
        set("owner_name", "冷如冰");
        set_temp("owner", "rubing");
        set_temp("owner_name", "冷如冰");
        ::setup();
}
