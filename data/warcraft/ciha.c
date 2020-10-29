// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("驴[2;37;0m[2;37;0m", ({"gyill"}));        
        set("gender", "女性");                
        set("long", "无[2;37;0m
它是眼一一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ciha");
        set("owner_name", "眼一一");
        set_temp("owner", "ciha");
        set_temp("owner_name", "眼一一");
        ::setup();
}
