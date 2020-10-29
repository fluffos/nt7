// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("中文[2;37;0m[2;37;0m", ({"zuoji"}));        
        set("gender", "男性");                
        set("long", "中文[2;37;0m
它是系系的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wjysjcd");
        set("owner_name", "系系");
        set_temp("owner", "wjysjcd");
        set_temp("owner_name", "系系");
        ::setup();
}
