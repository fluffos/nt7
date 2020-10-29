// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;35m小泽玛利亚[2;37;0m[2;37;0m", ({"xoxo"}));        
        set("gender", "女性");                
        set("long", "小泽玛利亚同时有着西方女优的狂野性感和东方女性的温柔唯美。[2;37;0m
它是耶稣的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yes");
        set("owner_name", "耶稣");
        set_temp("owner", "yes");
        set_temp("owner_name", "耶稣");
        ::setup();
}
