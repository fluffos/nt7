// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是丸匹皮的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wanpp");
        set("owner_name", "丸匹皮");
        set_temp("owner", "wanpp");
        set_temp("owner_name", "丸匹皮");
        ::setup();
}
