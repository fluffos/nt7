// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("天[2;37;0m[2;37;0m", ({"choose"}));        
        set("gender", "女性");                
        set("long", "天[2;37;0m
它是风贰的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "iankd");
        set("owner_name", "风贰");
        set_temp("owner", "iankd");
        set_temp("owner_name", "风贰");
        ::setup();
}
