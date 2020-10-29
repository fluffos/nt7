// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m不败玄武[2;37;0m[2;37;0m", ({"choufengs"}));        
        set("gender", "女性");                
        set("long", "不败玄武[2;37;0m
它是抽风的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "choufeng");
        set("owner_name", "抽风");
        set_temp("owner", "choufeng");
        set_temp("owner_name", "抽风");
        ::setup();
}
