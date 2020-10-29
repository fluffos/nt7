// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m客官[1;33m[2;37;0m[2;37;0m", ({"dustmm"}));        
        set("gender", "男性");                
        set("long", "啦啦啦[2;37;0m
它是客官别走的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dust");
        set("owner_name", "客官别走");
        set_temp("owner", "dust");
        set_temp("owner_name", "客官别走");
        ::setup();
}
