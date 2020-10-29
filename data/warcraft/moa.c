// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;32m忍[34m者[1;33m神[35m龟[2;37;0m[2;37;0m", ({"mojiao"}));        
        set("gender", "男性");                
        set("long", "公共卫生[2;37;0m
它是魔教弟子的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "moa");
        set("owner_name", "魔教弟子");
        set_temp("owner", "moa");
        set_temp("owner_name", "魔教弟子");
        ::setup();
}
