// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m小马[2;37;0m[2;37;0m", ({"xiaoma"}));        
        set("gender", "男性");                
        set("long", "$HIG$小马[2;37;0m
它是嗨哥的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "hhb");
        set("owner_name", "嗨哥");
        set_temp("owner", "hhb");
        set_temp("owner_name", "嗨哥");
        ::setup();
}
