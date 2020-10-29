// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;34m爱骑[2;37;0m[2;37;0m", ({"ilovelong"}));        
        set("gender", "男性");                
        set("long", "$BLINK$$HIB$爱骑[2;37;0m
它是吕娟的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lvjuan");
        set("owner_name", "吕娟");
        set_temp("owner", "lvjuan");
        set_temp("owner_name", "吕娟");
        ::setup();
}
