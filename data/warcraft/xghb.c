// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小马[2;37;0m[2;37;0m", ({"aaac"}));        
        set("gender", "男性");                
        set("long", "finger[2;37;0m
它是布袋一的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xghb");
        set("owner_name", "布袋一");
        set_temp("owner", "xghb");
        set_temp("owner_name", "布袋一");
        ::setup();
}
