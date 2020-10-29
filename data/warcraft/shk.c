// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙卷风[2;37;0m[2;37;0m", ({"waa"}));        
        set("gender", "男性");                
        set("long", "龙卷风[2;37;0m
它是娃娲娲的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "shk");
        set("owner_name", "娃娲娲");
        set_temp("owner", "shk");
        set_temp("owner_name", "娃娲娲");
        ::setup();
}
