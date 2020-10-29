// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;33m地坤势[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "说死你。[2;37;0m
它是不老仙的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "like");
        set("owner_name", "不老仙");
        set_temp("owner", "like");
        set_temp("owner_name", "不老仙");
        ::setup();
}
