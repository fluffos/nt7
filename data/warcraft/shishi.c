// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("完毕[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "完毕[2;37;0m
它是大头的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "shishi");
        set("owner_name", "大头");
        set_temp("owner", "shishi");
        set_temp("owner_name", "大头");
        ::setup();
}
