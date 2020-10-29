// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("骡子[2;37;0m[2;37;0m", ({"luozi"}));        
        set("gender", "男性");                
        set("long", "面向黄土，背向天，一天就知道干活[2;37;0m
它是欧阳杀的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ouyang");
        set("owner_name", "欧阳杀");
        set_temp("owner", "ouyang");
        set_temp("owner_name", "欧阳杀");
        ::setup();
}
