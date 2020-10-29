// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m好吃叫化鸡[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "$HIG$好吃叫化鸡[2;37;0m
它是伏猫降蛇的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "pupu");
        set("owner_name", "伏猫降蛇");
        set_temp("owner", "pupu");
        set_temp("owner_name", "伏猫降蛇");
        ::setup();
}
