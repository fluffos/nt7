// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("不亚[2;37;0m[2;37;0m", ({"firesfires"}));        
        set("gender", "男性");                
        set("long", "神秘兽[2;37;0m
它是不亚亚的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "fires");
        set("owner_name", "不亚亚");
        set_temp("owner", "fires");
        set_temp("owner_name", "不亚亚");
        ::setup();
}
