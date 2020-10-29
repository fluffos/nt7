// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m帅[2;37;0m[1;33m到[1;35m掉渣[2;37;0m[2;37;0m", ({"perfect"}));        
        set("gender", "男性");                
        set("long", "帅有很多种...[2;37;0m
它是帅有嗯种的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "gorgeous");
        set("owner_name", "帅有嗯种");
        set_temp("owner", "gorgeous");
        set_temp("owner_name", "帅有嗯种");
        ::setup();
}
