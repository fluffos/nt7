// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m风火戏红尘[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "嬉笑红尘[2;37;0m
它是刀中不二的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "baiyi");
        set("owner_name", "刀中不二");
        set_temp("owner", "baiyi");
        set_temp("owner_name", "刀中不二");
        ::setup();
}
