// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[41;1m[1;32m老鸨子[2;37;0m[2;37;0m", ({"laobao"}));        
        set("gender", "女性");                
        set("long", "丽春院 老鸨子[2;37;0m
它是皮条客的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "man");
        set("owner_name", "皮条客");
        set_temp("owner", "man");
        set_temp("owner_name", "皮条客");
        ::setup();
}
