// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;32m啦啦啦[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "女性");                
        set("long", "魔前一叩三千年，回首凡尘不做仙[2;37;0m
它是东风二号的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "worka");
        set("owner_name", "东风二号");
        set_temp("owner", "worka");
        set_temp("owner_name", "东风二号");
        ::setup();
}
