// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("足球[2;37;0m[2;37;0m", ({"zhuqiu"}));        
        set("gender", "男性");                
        set("long", "这是一只足球。[2;37;0m
它是西帅的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "verdisha");
        set("owner_name", "西帅");
        set_temp("owner", "verdisha");
        set_temp("owner_name", "西帅");
        ::setup();
}
