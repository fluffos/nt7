// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m冰[1;36m甲[1;36m龙[1;36m痕[2;37;0m[2;37;0m", ({"hoho"}));        
        set("gender", "男性");                
        set("long", "冰甲龙痕[2;37;0m
它是剑之初的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "winjo");
        set("owner_name", "剑之初");
        set_temp("owner", "winjo");
        set_temp("owner_name", "剑之初");
        ::setup();
}
