// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("三大类[2;37;0m[2;37;0m", ({"benz"}));        
        set("gender", "男性");                
        set("long", "           [2;37;0m
它是武当米的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wddm");
        set("owner_name", "武当米");
        set_temp("owner", "wddm");
        set_temp("owner_name", "武当米");
        ::setup();
}
