// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m凯美瑞[2;37;0m[2;37;0m", ({"camery"}));        
        set("gender", "男性");                
        set("long", "this is toyota camery[2;37;0m
它是渡电的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lighting");
        set("owner_name", "渡电");
        set_temp("owner", "lighting");
        set_temp("owner_name", "渡电");
        ::setup();
}
