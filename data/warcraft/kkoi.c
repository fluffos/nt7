// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m叶良辰[2;37;0m[2;37;0m", ({"yiyayo"}));        
        set("gender", "女性");                
        set("long", "的发放[2;37;0m
它是华十的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kkoi");
        set("owner_name", "华十");
        set_temp("owner", "kkoi");
        set_temp("owner_name", "华十");
        ::setup();
}
