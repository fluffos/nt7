// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙[2;37;0m[2;37;0m", ({"long"}));        
        set("gender", "男性");                
        set("long", "龙[2;37;0m
它是中神通的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "score");
        set("owner_name", "中神通");
        set_temp("owner", "score");
        set_temp("owner_name", "中神通");
        ::setup();
}
