// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("狂[2;37;0m[2;37;0m", ({"kuangf"}));        
        set("gender", "女性");                
        set("long", "狂风[2;37;0m
它是杰二的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "jieb");
        set("owner_name", "杰二");
        set_temp("owner", "jieb");
        set_temp("owner_name", "杰二");
        ::setup();
}
