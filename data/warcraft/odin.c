// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;36m斯莱普尼斯[2;37;0m[2;37;0m", ({"sleipnir"}));        
        set("gender", "男性");                
        set("long", "一匹毛白胜雪，有八只脚的神骏天马，奥丁骑着它环游世界。[2;37;0m
它是奥丁的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "odin");
        set("owner_name", "奥丁");
        set_temp("owner", "odin");
        set_temp("owner_name", "奥丁");
        ::setup();
}
