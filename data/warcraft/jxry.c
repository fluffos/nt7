// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("金鳞瑞兽[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "金鳞瑞兽 御风而来[2;37;0m
它是吉祥如意的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jxry");
        set("owner_name", "吉祥如意");
        set_temp("owner", "jxry");
        set_temp("owner_name", "吉祥如意");
        ::setup();
}
