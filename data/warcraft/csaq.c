// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小卡车[2;37;0m[2;37;0m", ({"csaqs"}));        
        set("gender", "男性");                
        set("long", "hi[2;37;0m
它是大花生的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "csaq");
        set("owner_name", "大花生");
        set_temp("owner", "csaq");
        set_temp("owner_name", "大花生");
        ::setup();
}
