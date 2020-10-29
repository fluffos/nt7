// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m的妹[2;37;0m[2;37;0m", ({"nvnv"}));        
        set("gender", "女性");                
        set("long", "的妹[2;37;0m
它是华小妹的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "huashanb");
        set("owner_name", "华小妹");
        set_temp("owner", "huashanb");
        set_temp("owner_name", "华小妹");
        ::setup();
}
