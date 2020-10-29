// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大的[2;37;0m[2;37;0m", ({"dami"}));        
        set("gender", "男性");                
        set("long", "大的[2;37;0m
它是胡一刀的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yidao");
        set("owner_name", "胡一刀");
        set_temp("owner", "yidao");
        set_temp("owner_name", "胡一刀");
        ::setup();
}
