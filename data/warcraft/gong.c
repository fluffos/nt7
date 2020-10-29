// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;36m西[1;32m村[1;33m理[35m香[2;37;0m[2;37;0m", ({"lady"}));        
        set("gender", "女性");                
        set("long", "好孩子[2;37;0m
它是公公最威的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "gong");
        set("owner_name", "公公最威");
        set_temp("owner", "gong");
        set_temp("owner_name", "公公最威");
        ::setup();
}
