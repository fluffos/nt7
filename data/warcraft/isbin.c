// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m胡[2;37;0m[2;37;0m", ({"lling"}));        
        set("gender", "女性");                
        set("long", "胡[2;37;0m
它是萧潜水的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "isbin");
        set("owner_name", "萧潜水");
        set_temp("owner", "isbin");
        set_temp("owner_name", "萧潜水");
        ::setup();
}
