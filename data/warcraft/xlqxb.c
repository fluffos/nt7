// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;36m三刀流[2;37;0m[2;37;0m", ({"sandaoliu"}));        
        set("gender", "女性");                
        set("long", "玄武是什么东西。[2;37;0m
它是索隆的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "xlqxb");
        set("owner_name", "索隆");
        set_temp("owner", "xlqxb");
        set_temp("owner_name", "索隆");
        ::setup();
}
