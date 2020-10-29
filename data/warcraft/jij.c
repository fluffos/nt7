// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m囚牛[2;37;0m[2;37;0m", ({"xiaoq"}));        
        set("gender", "男性");                
        set("long", "龙老大[2;37;0m
它是有爱就做的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "jij");
        set("owner_name", "有爱就做");
        set_temp("owner", "jij");
        set_temp("owner_name", "有爱就做");
        ::setup();
}
