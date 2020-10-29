// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("初级坑[2;37;0m[2;37;0m", ({"cjk"}));        
        set("gender", "女性");                
        set("long", "finish[2;37;0m
它是周丹壹的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "bta");
        set("owner_name", "周丹壹");
        set_temp("owner", "bta");
        set_temp("owner_name", "周丹壹");
        ::setup();
}
