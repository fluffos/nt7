// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小白虎[2;37;0m[2;37;0m", ({"xiaobai"}));        
        set("gender", "男性");                
        set("long", "一直小白虎[2;37;0m
它是迪亚的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "ambrose");
        set("owner_name", "迪亚");
        set_temp("owner", "ambrose");
        set_temp("owner_name", "迪亚");
        ::setup();
}
