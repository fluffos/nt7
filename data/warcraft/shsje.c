// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火麒麟[2;37;0m[2;37;0m", ({"qiling"}));        
        set("gender", "男性");                
        set("long", "火麒麟[2;37;0m
它是小东邪的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "shsje");
        set("owner_name", "小东邪");
        set_temp("owner", "shsje");
        set_temp("owner_name", "小东邪");
        ::setup();
}
