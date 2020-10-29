// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "秘密[2;37;0m
它是大亨的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "thz");
        set("owner_name", "大亨");
        set_temp("owner", "thz");
        set_temp("owner_name", "大亨");
        ::setup();
}
