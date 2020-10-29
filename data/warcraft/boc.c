// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m双汇火腿肠[2;37;0m[2;37;0m", ({"iboc"}));        
        set("gender", "男性");                
        set("long", "丹房[2;37;0m
它是中行的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "boc");
        set("owner_name", "中行");
        set_temp("owner", "boc");
        set_temp("owner_name", "中行");
        ::setup();
}
