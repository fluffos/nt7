// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m万[1;31m年[1;32m神木[2;37;0m[2;37;0m", ({"doggy"}));        
        set("gender", "女性");                
        set("long", "doddy[2;37;0m
它是华山小生的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lohaniii");
        set("owner_name", "华山小生");
        set_temp("owner", "lohaniii");
        set_temp("owner_name", "华山小生");
        ::setup();
}
