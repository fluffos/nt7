// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m小大众[2;37;0m[2;37;0m", ({"zsw"}));        
        set("gender", "女性");                
        set("long", "薇薇的小POLO[2;37;0m
它是唐薇薇的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "weiwei");
        set("owner_name", "唐薇薇");
        set_temp("owner", "weiwei");
        set_temp("owner_name", "唐薇薇");
        ::setup();
}
