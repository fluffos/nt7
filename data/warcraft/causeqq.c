// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小妞[2;37;0m[2;37;0m", ({"ababab"}));        
        set("gender", "男性");                
        set("long", "小妞[2;37;0m
它是牛六的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "causeqq");
        set("owner_name", "牛六");
        set_temp("owner", "causeqq");
        set_temp("owner_name", "牛六");
        ::setup();
}
