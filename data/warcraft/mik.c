// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("烈酒[2;37;0m[2;37;0m", ({"cheung"}));        
        set("gender", "男性");                
        set("long", "烈酒[2;37;0m
它是张烈的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "mik");
        set("owner_name", "张烈");
        set_temp("owner", "mik");
        set_temp("owner_name", "张烈");
        ::setup();
}
