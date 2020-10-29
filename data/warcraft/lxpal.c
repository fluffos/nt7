// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m莫莉[2;37;0m[2;37;0m", ({"molly"}));        
        set("gender", "女性");                
        set("long", "全身火红的小家伙[2;37;0m
它是心结石的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lxpal");
        set("owner_name", "心结石");
        set_temp("owner", "lxpal");
        set_temp("owner_name", "心结石");
        ::setup();
}
