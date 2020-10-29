// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m狂[1;36m风[2;37;0m[2;37;0m[2;37;0m", ({"phome"}));        
        set("gender", "男性");                
        set("long", "一阵风[2;37;0m
它是亚夜风的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "loume");
        set("owner_name", "亚夜风");
        set_temp("owner", "loume");
        set_temp("owner_name", "亚夜风");
        ::setup();
}
