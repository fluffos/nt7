// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m追风黄金兽[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这就是传说中的八骏，浑身金黄锦缎似的，龙相虎步、日行万里。[2;37;0m
它是鲁智深的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "luda");
        set("owner_name", "鲁智深");
        set_temp("owner", "luda");
        set_temp("owner_name", "鲁智深");
        ::setup();
}
