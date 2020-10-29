// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m汗血宝马[2;37;0m[2;37;0m", ({"bmw"}));        
        set("gender", "女性");                
        set("long", "气死富二代，不让官二代[2;37;0m
它是郭芙的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "guofu");
        set("owner_name", "郭芙");
        set_temp("owner", "guofu");
        set_temp("owner_name", "郭芙");
        ::setup();
}
