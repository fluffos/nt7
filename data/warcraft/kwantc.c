// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m小紫[2;37;0m[2;37;0m", ({"xiaozi"}));        
        set("gender", "女性");                
        set("long", "一只紫色的朱雀[2;37;0m
它是小璇的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "kwantc");
        set("owner_name", "小璇");
        set_temp("owner", "kwantc");
        set_temp("owner_name", "小璇");
        ::setup();
}
