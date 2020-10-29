// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m鼠标[2;37;0m[2;37;0m", ({"mouse"}));        
        set("gender", "男性");                
        set("long", "一只无线鼠标。[2;37;0m
它是比尔盖茨的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jojo");
        set("owner_name", "比尔盖茨");
        set_temp("owner", "jojo");
        set_temp("owner_name", "比尔盖茨");
        ::setup();
}
