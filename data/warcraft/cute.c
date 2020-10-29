// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小可爱[2;37;0m[2;37;0m", ({"waa"}));        
        set("gender", "女性");                
        set("long", "小可爱[2;37;0m
它是娲娃的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cute");
        set("owner_name", "娲娃");
        set_temp("owner", "cute");
        set_temp("owner_name", "娲娃");
        ::setup();
}
