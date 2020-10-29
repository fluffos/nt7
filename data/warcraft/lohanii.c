// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m皮卡丘[2;37;0m[2;37;0m", ({"pikachu"}));        
        set("gender", "女性");                
        set("long", "魔幻兽[2;37;0m
它是明罗的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lohanii");
        set("owner_name", "明罗");
        set_temp("owner", "lohanii");
        set_temp("owner_name", "明罗");
        ::setup();
}
