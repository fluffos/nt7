// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小龙龙[2;37;0m[2;37;0m", ({"ryqinglong"}));        
        set("gender", "男性");                
        set("long", "小龙龙[2;37;0m
它是中萧的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "rylowek");
        set("owner_name", "中萧");
        set_temp("owner", "rylowek");
        set_temp("owner_name", "中萧");
        ::setup();
}
