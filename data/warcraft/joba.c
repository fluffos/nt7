// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("啦啦啦[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "啦啦啦[2;37;0m
它是劳动人民的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "joba");
        set("owner_name", "劳动人民");
        set_temp("owner", "joba");
        set_temp("owner_name", "劳动人民");
        ::setup();
}
