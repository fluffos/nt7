// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m逢赌必赢神龙[2;37;0m[2;37;0m", ({"gushenpet"}));        
        set("gender", "女性");                
        set("long", "一只能让主人逢赌必赢的神龙[2;37;0m
它是股神的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "gushen");
        set("owner_name", "股神");
        set_temp("owner", "gushen");
        set_temp("owner_name", "股神");
        ::setup();
}
