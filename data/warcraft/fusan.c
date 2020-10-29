// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m紫[1;31m焰[1;33m心[2;37;0m[2;37;0m", ({"heart"}));        
        set("gender", "女性");                
        set("long", "修真专用 秘宝永流传[2;37;0m
它是傅山的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fusan");
        set("owner_name", "傅山");
        set_temp("owner", "fusan");
        set_temp("owner_name", "傅山");
        ::setup();
}
