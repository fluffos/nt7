// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老马[2;37;0m[2;37;0m", ({"xue_"}));        
        set("gender", "男性");                
        set("long", "老马[2;37;0m
它是一抹红尘的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "qianmr");
        set("owner_name", "一抹红尘");
        set_temp("owner", "qianmr");
        set_temp("owner_name", "一抹红尘");
        ::setup();
}
