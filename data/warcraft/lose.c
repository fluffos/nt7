// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小咖啡龙[2;37;0m[2;37;0m", ({"uccu"}));        
        set("gender", "男性");                
        set("long", "小咖啡龙[2;37;0m
它是幻影模工的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lose");
        set("owner_name", "幻影模工");
        set_temp("owner", "lose");
        set_temp("owner_name", "幻影模工");
        ::setup();
}
