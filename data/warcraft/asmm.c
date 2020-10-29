// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火鸟[2;37;0m[2;37;0m", ({"turkey"}));        
        set("gender", "女性");                
        set("long", "hit chelonian[2;37;0m
它是决明子的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "asmm");
        set("owner_name", "决明子");
        set_temp("owner", "asmm");
        set_temp("owner_name", "决明子");
        ::setup();
}
