// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m萝[1;33m拉[2;37;0m[2;37;0m", ({"baidu"}));        
        set("gender", "女性");                
        set("long", "网络红人  国宝级美女[2;37;0m
它是晚静的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "iiidc");
        set("owner_name", "晚静");
        set_temp("owner", "iiidc");
        set_temp("owner_name", "晚静");
        ::setup();
}
