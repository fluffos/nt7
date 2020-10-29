// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("日[2;37;0m[2;37;0m", ({"fuck"}));        
        set("gender", "男性");                
        set("long", "日[2;37;0m
它是弯刀的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wandao");
        set("owner_name", "弯刀");
        set_temp("owner", "wandao");
        set_temp("owner_name", "弯刀");
        ::setup();
}
