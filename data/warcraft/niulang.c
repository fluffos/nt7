// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;35m印度[1;32m神[1;31m牛[2;37;0m[2;37;0m", ({"niu"}));        
        set("gender", "男性");                
        set("long", "一条来自印度的神牛……[2;37;0m
它是牛郎的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "niulang");
        set("owner_name", "牛郎");
        set_temp("owner", "niulang");
        set_temp("owner_name", "牛郎");
        ::setup();
}
