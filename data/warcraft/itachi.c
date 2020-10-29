// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("幻龙[2;37;0m[2;37;0m", ({"shou"}));        
        set("gender", "男性");                
        set("long", "勇猛无比[2;37;0m
它是段雨龙的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "itachi");
        set("owner_name", "段雨龙");
        set_temp("owner", "itachi");
        set_temp("owner_name", "段雨龙");
        ::setup();
}
