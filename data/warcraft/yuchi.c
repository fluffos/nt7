// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m赤焰[5m[1;34m闪电兽[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这匹马全身火炭般赤红，追风逐电、神骏非常。[2;37;0m
它是尉迟恭的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yuchi");
        set("owner_name", "尉迟恭");
        set_temp("owner", "yuchi");
        set_temp("owner_name", "尉迟恭");
        ::setup();
}
