// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "一头麒麟[2;37;0m
它是大蝈蝈的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "emsc");
        set("owner_name", "大蝈蝈");
        set_temp("owner", "emsc");
        set_temp("owner_name", "大蝈蝈");
        ::setup();
}
