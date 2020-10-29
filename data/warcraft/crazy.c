// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("上古神龙[2;37;0m[2;37;0m", ({"dragon"}));        
        set("gender", "女性");                
        set("long", "一之神兽[2;37;0m
它是疯子的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "crazy");
        set("owner_name", "疯子");
        set_temp("owner", "crazy");
        set_temp("owner_name", "疯子");
        ::setup();
}
