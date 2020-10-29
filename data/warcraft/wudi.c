// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小仓优子[2;37;0m[2;37;0m", ({"plgp"}));        
        set("gender", "男性");                
        set("long", "@miaoshu[2;37;0m
它是欧阳无敌的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wudi");
        set("owner_name", "欧阳无敌");
        set_temp("owner", "wudi");
        set_temp("owner_name", "欧阳无敌");
        ::setup();
}
