// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m完颜[1;33m洪烈[2;37;0m[2;37;0m", ({"wyhl"}));        
        set("gender", "女性");                
        set("long", "一只朱雀。[2;37;0m
它是包惜弱的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "jojogbq");
        set("owner_name", "包惜弱");
        set_temp("owner", "jojogbq");
        set_temp("owner_name", "包惜弱");
        ::setup();
}
