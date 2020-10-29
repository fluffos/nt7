// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("三丫麒麟[2;37;0m[2;37;0m", ({"whcride"}));        
        set("gender", "女性");                
        set("long", "三丫麒麟[2;37;0m
它是吴三丫的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "whc");
        set("owner_name", "吴三丫");
        set_temp("owner", "whc");
        set_temp("owner_name", "吴三丫");
        ::setup();
}
