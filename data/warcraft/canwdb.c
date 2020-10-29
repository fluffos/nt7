// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m流云[2;37;0m[2;37;0m", ({"que"}));        
        set("gender", "男性");                
        set("long", "这是一只叫流云的鸟，很普通..[2;37;0m
它是铁血舞裳的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "canwdb");
        set("owner_name", "铁血舞裳");
        set_temp("owner", "canwdb");
        set_temp("owner_name", "铁血舞裳");
        ::setup();
}
