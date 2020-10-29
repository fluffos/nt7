// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火[1;37m[2;37;0m[2;37;0m", ({"xxl"}));        
        set("gender", "女性");                
        set("long", "猪一只[2;37;0m
它是小虾米的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wps");
        set("owner_name", "小虾米");
        set_temp("owner", "wps");
        set_temp("owner_name", "小虾米");
        ::setup();
}
