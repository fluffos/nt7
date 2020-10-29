// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("琪琪[2;37;0m[2;37;0m", ({"qil"}));        
        set("gender", "男性");                
        set("long", "一只小土狗[2;37;0m
它是韩研儿的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "hanbuo");
        set("owner_name", "韩研儿");
        set_temp("owner", "hanbuo");
        set_temp("owner_name", "韩研儿");
        ::setup();
}
