// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "怪[2;37;0m
它是大眼怪的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "gonghs");
        set("owner_name", "大眼怪");
        set_temp("owner", "gonghs");
        set_temp("owner_name", "大眼怪");
        ::setup();
}
