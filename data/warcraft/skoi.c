// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m小幂幂[2;37;0m[2;37;0m", ({"yiyayo"}));        
        set("gender", "女性");                
        set("long", "阿道夫[2;37;0m
它是天知道的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "skoi");
        set("owner_name", "天知道");
        set_temp("owner", "skoi");
        set_temp("owner_name", "天知道");
        ::setup();
}
