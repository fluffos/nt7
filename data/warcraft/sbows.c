// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m幸福二五零[2;37;0m[2;37;0m", ({"xingfu"}));        
        set("gender", "女性");                
        set("long", "幸福250 经典摩托 250cc[2;37;0m
它是阿九的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "sbows");
        set("owner_name", "阿九");
        set_temp("owner", "sbows");
        set_temp("owner_name", "阿九");
        ::setup();
}
