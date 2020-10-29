// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m凤翔[2;37;0m[2;37;0m", ({"xiu"}));        
        set("gender", "女性");                
        set("long", "九天[2;37;0m
它是上官金虹的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xxiu");
        set("owner_name", "上官金虹");
        set_temp("owner", "xxiu");
        set_temp("owner_name", "上官金虹");
        ::setup();
}
