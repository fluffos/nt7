// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("乐乐[2;37;0m[2;37;0m", ({"mineraride"}));        
        set("gender", "男性");                
        set("long", "看什么看，没见过那么帅的麒麟？[2;37;0m
它是牛一的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "minera");
        set("owner_name", "牛一");
        set_temp("owner", "minera");
        set_temp("owner_name", "牛一");
        ::setup();
}
