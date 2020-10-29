// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("万用插[2;37;0m[2;37;0m", ({"usb"}));        
        set("gender", "男性");                
        set("long", "dsjjdjs[2;37;0m
它是血刀的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "gera");
        set("owner_name", "血刀");
        set_temp("owner", "gera");
        set_temp("owner_name", "血刀");
        ::setup();
}
